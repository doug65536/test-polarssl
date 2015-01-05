#include <iostream>
#include <QByteArray>
#include <QString>
#include <QDebug>

#include "polarssl/aes.h"

QByteArray decryptStory(QByteArray data, QString keyStr, QString ivStr){
    QByteArray key = keyStr.toUtf8();
    QByteArray iv = ivStr.toUtf8();


    char *ckey = key.data();
    char *ivec = iv.data();

    char *indata = data.data();
    char outdata[data.length()];

    aes_context ctx;

    aes_setkey_dec(&ctx, (const unsigned char*)ckey, 128);

    int ret = aes_crypt_cbc(&ctx, AES_DECRYPT, data.size(), (unsigned char*)ivec, (const unsigned char*)indata, (unsigned char*)outdata);

    QByteArray decrypted = QByteArray((const char*) outdata, data.length());

    if(ret == 0){
        qDebug() << "Success";
    }else{
        qDebug() << "Failed";
    }


    return decrypted;
}

int main()
{
    QString test, key, iv, result;
    QByteArray encryptedData, outputData;

    test = "Hello polarssl";
    key = "bad passwords are bad";
    iv = "initialization vectors make me tear up with happiness";

    encryptedData = decryptStory(test.toUtf8(), key, iv);
    outputData = decryptStory(encryptedData, key, iv);
    result = result.fromUtf8(outputData);
    std::cout << result.toStdString() << std::endl;
}
