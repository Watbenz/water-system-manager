#include "EasyFirebase.h"
#include "FirebaseESP32.h"
#include ".\..\Constant\Constant.h"

void EasyFirebase::init()
{
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    Firebase.setReadTimeout(fbdo, FIREBASE_TIMEOUT);
    Firebase.setwriteSizeLimit(fbdo, "tiny");
    Firebase.setDoubleDigits(6);
}

void EasyFirebase::printError()
{
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
}

void EasyFirebase::printSuccess()
{
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
    Serial.println("ETag: " + fbdo.ETag());
    Serial.print("VALUE: ");
    printResult();
    Serial.println("------------------------------------");
    Serial.println();
}

void EasyFirebase::printResult()
{
    if (fbdo.dataType() == "int")
        Serial.println(fbdo.intData());
    else if (fbdo.dataType() == "float")
        Serial.println(fbdo.floatData(), 5);
    else if (fbdo.dataType() == "double")
        printf("%.9lf\n", fbdo.doubleData());
    else if (fbdo.dataType() == "boolean")
        Serial.println(fbdo.boolData() == 1 ? "true" : "false");
    else if (fbdo.dataType() == "string")
        Serial.println(fbdo.stringData());
    else if (fbdo.dataType() == "json")
        printJson();
    else if (fbdo.dataType() == "array")
        printArray();
    else if (fbdo.dataType() == "blob")
        printBlob();
    else if (fbdo.dataType() == "file")
        printFile();
    else
        Serial.println(fbdo.payload());
}

void EasyFirebase::printJson()
{
    Serial.println();
    FirebaseJson &json = fbdo.jsonObject();
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
        json.iteratorGet(i, type, key, value);
        Serial.print(i);
        Serial.print(", ");
        Serial.print("Type: ");
        Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
        if (type == FirebaseJson::JSON_OBJECT)
        {
            Serial.print(", Key: ");
            Serial.print(key);
        }
        Serial.print(", Value: ");
        Serial.println(value);
    }
    json.iteratorEnd();
}

void EasyFirebase::printArray()
{
    Serial.println();
    FirebaseJsonArray &arr = fbdo.jsonArray();
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
        Serial.print(i);
        Serial.print(", Value: ");

        FirebaseJsonData &jsonData = fbdo.jsonData();
        //Get the result data from FirebaseJsonArray object
        arr.get(jsonData, i);
        if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
            Serial.println(jsonData.boolValue ? "true" : "false");
        else if (jsonData.typeNum == FirebaseJson::JSON_INT)
            Serial.println(jsonData.intValue);
        else if (jsonData.typeNum == FirebaseJson::JSON_FLOAT)
            Serial.println(jsonData.floatValue);
        else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
            printf("%.9lf\n", jsonData.doubleValue);
        else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
                 jsonData.typeNum == FirebaseJson::JSON_NULL ||
                 jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
                 jsonData.typeNum == FirebaseJson::JSON_ARRAY)
            Serial.println(jsonData.stringValue);
    }
}

void EasyFirebase::printBlob()
{
    Serial.println();

    for (size_t i = 0; i < fbdo.blobData().size(); i++)
    {
        if (i > 0 && i % 16 == 0)
            Serial.println();

        if (i < 16)
            Serial.print("0");

        Serial.print(fbdo.blobData()[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void EasyFirebase::printFile()
{
    Serial.println();

    File file = fbdo.fileStream();
    int i = 0;

    while (file.available())
    {
        if (i > 0 && i % 16 == 0)
            Serial.println();

        int v = file.read();

        if (v < 16)
            Serial.print("0");

        Serial.print(v, HEX);
        Serial.print(" ");
        i++;
    }
    Serial.println();
    file.close();
}

void EasyFirebase::writeDouble(String &path, double data)
{
    if (Firebase.setDouble(fbdo, path, data))
        printSuccess();
    else
        printError();
}

double EasyFirebase::readDouble(String &path)
{
    if (Firebase.getDouble(fbdo, path))
        return fbdo.doubleData();
    else
        printError();
    return 0.0;
}

void EasyFirebase::writeInt(String &path, int data)
{
    if (Firebase.setInt(fbdo, path, data))
        printSuccess();
    else
        printError();
}

int EasyFirebase::readInt(String &path)
{
    if (Firebase.getInt(fbdo, path))
        return fbdo.intData();
    else
        printError();
    return 0;
}

String EasyFirebase::readString(String &path)
{
    if (Firebase.getString(fbdo, path))
        return fbdo.stringData();
    else
        printError();
    return "Error";
}

void EasyFirebase::writeString(String &path, String &data)
{
    if (Firebase.setString(fbdo, path, data))
        printSuccess();
    else
        printError();
}

void EasyFirebase::deleteNode(String &path)
{
    Firebase.deleteNode(fbdo, path);
}

void EasyFirebase::updateNode(String &path, FirebaseJson json) {
    if (Firebase.updateNode(fbdo, path, json)) {
        printSuccess();
    }
    else {
        printError();
    }
}
