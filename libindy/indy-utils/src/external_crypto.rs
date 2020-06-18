extern crate libc;

use super::ErrorCode;
use super::sequence;
use serde::{Serialize, Serializer};
use serde_json::Result;
use self::libc::c_char;
use lazy_static::lazy_static;

use std::collections::{HashMap, VecDeque};
use std::ffi::{CString, CStr};
use std::str::Utf8Error;
use std::sync::Mutex;
use std::slice;
use sodiumoxide::crypto::aead::chacha20poly1305_ietf;
use sodiumoxide::crypto::auth::hmacsha256;
use indy_api_types::CommandHandle;

static mut encResultLen: u32 = 0;
static mut decResultLen: u32 = 0;

pub struct ExternalCrypto {
}

impl ExternalCrypto {
    #[no_mangle]
    pub extern "C" fn indy_register_tee_method(key_gen: extern "C" fn() -> (),
                                               enc: extern "C" fn(xcommand_handle: CommandHandle, t: *const u8, l: u32, resultLen: *mut u32) -> *const u8,
                                               dec: extern "C" fn(xcommand_handle: CommandHandle, t: *const u8, l: u32, resultLen: *mut u32) -> *const u8) -> ErrorCode {
        unsafe {
            key_gen_tee = Some(key_gen);
            encrypt_tee = Some(enc);
            decrypt_tee = Some(dec);
        }

        ErrorCode::Success
    }

    pub unsafe fn indy_encrypt_tee(msg: &Vec<u8>) -> &[u8] {
        if encrypt_tee.is_some() {
            let result = encrypt_tee.unwrap()(9102312, msg.as_ptr(), msg.len() as u32, &mut encResultLen);
            slice::from_raw_parts(result, encResultLen as usize)
        } else {
            msg.as_ref()
        }
    }

    pub unsafe fn indy_decrypt_tee(msg: Vec<u8>) -> Vec<u8> {
        if decrypt_tee.is_some() {
            let f = decrypt_tee.unwrap()(9102313, msg.as_ptr(), msg.len() as u32, &mut decResultLen);
            slice::from_raw_parts(f, decResultLen as usize).to_vec()
        } else {
            msg
        }
    }

    pub unsafe fn indy_create_key() {
        if key_gen_tee.is_some() {
            key_gen_tee.unwrap()();
        } else {
        }
    }
}

pub static mut key_gen_tee: Option<extern fn()> = None;
pub static mut encrypt_tee: Option<extern fn(xcommand_handle: CommandHandle, t: *const u8, l: u32, resultLen: *mut u32) -> *const u8> = None;
pub static mut decrypt_tee: Option<extern fn(xcommand_handle: CommandHandle, t: *const u8, l: u32, resultLen: *mut u32) -> *const u8> = None;
