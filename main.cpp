#include <iostream>
#include <QByteArray>
#include <QString>
#include <QDebug>

#include "polarssl/aes.h"
#include "polarssl/aes.h"

QByteArray decryptStory(QByteArray data, QString keyStr, QString ivStr){
    QByteArray result;

    QByteArray key = keyStr.toUtf8();
    QByteArray iv = ivStr.toUtf8();

    result.resize(data.size());

    aes_context ctx;
    //aes_init(&ctx);

    aes_setkey_dec(&ctx, (const unsigned char*)key.data(), key.size()*8);

    int ret = aes_crypt_cbc(&ctx, AES_DECRYPT,
                            data.size(),
                            (unsigned char*)iv.data(),
                            (const unsigned char*)data.data(),
                            (unsigned char*)result.data());

    if(ret == 0){
        qDebug() << "Success";
    }else{
        qDebug() << "Failed";
    }


    return result;
}

int main()
{
    QString test, key, iv, result;
    QByteArray encryptedData, outputData;

    test = "Hello polarssl!!";
    key  = "bad passwords ar";
    iv   = "initialization v";

    encryptedData = decryptStory(test.toUtf8(), key, iv);
    outputData = decryptStory(encryptedData, key, iv);
    result = result.fromUtf8(outputData);
    std::cout << result.toStdString() << std::endl;
}
