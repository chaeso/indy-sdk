package com.sk.secureindydemo

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import java.io.IOException
import java.security.KeyStoreException
import java.security.NoSuchAlgorithmException
import java.security.UnrecoverableEntryException
import java.security.cert.CertificateException


class MainActivity : AppCompatActivity() {

    private val TAG = "crypto"
    private val SAMPLE_ALIAS = "MYALIAS"

    override fun onCreate(savedInstanceState: Bundle?) {
        var decryptor = DeCryptor()
        var encryptor = EnCryptor()

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        try {
            val encryptedText = encryptor
                .encryptText(SAMPLE_ALIAS, "1klsajdflkjaskldfjaklsjdfklajsf11112123123123123hello world")
            Log.d(TAG, encryptedText.toString())

            Log.d(TAG, "decrypted data: "+decryptor.decryptData(SAMPLE_ALIAS, encryptedText, encryptor.getIv()))

        } catch (e: Exception) {
            Log.d(TAG, "exeption happens!")
            e.printStackTrace()
        }

//        print("--------------- encryptText() ---------------")
//        val z = encryptor.encryptText("aliaskkk", "hello world")
//        print(z)

//        println("start to create key")
//        Log.d("crypto","hello world!!")
//
//        val alias = "h"
//
//        val kpg: KeyPairGenerator = KeyPairGenerator.getInstance(
//                KeyProperties.KEY_ALGORITHM_EC,
//                "AndroidKeyStore"
//        )
//        val parameterSpec: KeyGenParameterSpec = KeyGenParameterSpec.Builder(
//                alias,
//                KeyProperties.PURPOSE_SIGN or KeyProperties.PURPOSE_VERIFY
//        ).run {
//            setDigests(KeyProperties.DIGEST_SHA256, KeyProperties.DIGEST_SHA512)
//            build()
//        }
//
//        kpg.initialize(parameterSpec)
//
//        val kp = kpg.generateKeyPair()
//
//        Log.d("crypto",kp.private.toString())
//        Log.d("crypto",kp.public.toString())
//
//        Log.d("crypto", "step1")
//        val ks: KeyStore = KeyStore.getInstance("AndroidKeyStore").apply {
//            load(null)
//        }
//
//        val data = ByteBuffer.allocate(100);
//
//        Log.d("crypto","step2")
//
////        val signature: ByteArray = Signature.getInstance("SHA256withECDSA").run {
////            initSign(kp.private)
////            update(data)
////            sign()
////        }
////        Log.d("crypto", "signature mode")
////        Log.d("crypto", signature.toString())  //[B@f1cf16e
//
//        // https://medium.com/@josiassena/using-the-android-keystore-system-to-store-sensitive-information-3a56175a454b
//
//        for (provider in Security.getProviders()) {
//            for ((key, value) in provider.entries) {
//                if ((value as String).contains("GCM")) {
//                    System.out.printf("key: [%s]  value: [%s]%n",
//                            key,
//                            value)
//                }
//            }
//        }
//
//        val cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING")
//
//        cipher.init(Cipher.ENCRYPT_MODE, kp.public)
//        val bytes = cipher.doFinal("hello world".toByteArray())
//        Log.d("crypto", Base64.encodeToString(bytes, Base64.DEFAULT))
    }
}