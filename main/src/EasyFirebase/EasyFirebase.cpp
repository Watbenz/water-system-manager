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

void EasyFirebase::writeDouble(const String &path, double data)
{
    if (Firebase.setDouble(fbdo, path, data))
        printSuccess();
    else
        printError();
}

double EasyFirebase::readDouble(const String &path)
{
    if (Firebase.getDouble(fbdo, path))
        return fbdo.doubleData();
    else
        printError();
    return 0.0;
}

bool EasyFirebase::hasDouble(const String &path)
{
    return Firebase.getDouble(fbdo, path);
}

void EasyFirebase::writeInt(const String &path, int data)
{
    if (Firebase.setInt(fbdo, path, data))
        printSuccess();
    else
        printError();
}

int EasyFirebase::readInt(const String &path)
{
    if (Firebase.getInt(fbdo, path))
        return fbdo.intData();
    else
        printError();
    return -1;
}

bool EasyFirebase::hasInt(const String &path)
{
    return Firebase.getInt(fbdo, path);
}

String EasyFirebase::readString(const String &path)
{
    if (Firebase.getString(fbdo, path))
        return fbdo.stringData();
    else
        printError();
    return "Error";
}

bool EasyFirebase::hasString(const String &path)
{
    return Firebase.getString(fbdo, path);
}

void EasyFirebase::writeString(const String &path, const String &data)
{
    if (Firebase.setString(fbdo, path, data))
        printSuccess();
    else
        printError();
}

void EasyFirebase::deleteNode(const String &path)
{
    Firebase.deleteNode(fbdo, path);
}

void EasyFirebase::clearAllNodeExcept(const String &path, int *excepts)
{
    //     FirebaseJsonData jsonData;
    //     FirebaseJson myJson;

    //     //Get FirebaseJson data
    //     jsonData.getJSON(myJson);

    //     //Parse the JSON object as list
    //     //Get the number of items
    //     size_t len = myJson.iteratorBegin();
    //     String key, value = "";
    //     int type = 0;
    //     for (size_t i = 0; i < len; i++)
    //     {
    //         //Get the item at index i, whereas key and value are the returned data
    //         myJson.iteratorGet(i, type, key, value);
    //         //Print the data
    //         Serial.print(i);
    //         Serial.print(", ");
    //         Serial.print("Type: ");
    //         Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
    //         if (type == FirebaseJson::JSON_OBJECT)
    //         {
    //             Serial.print(", Key: ");
    //             Serial.print(key);
    //         }
    //         Serial.print(", Value: ");
    //         Serial.println(value);
    //     }
    //     //Clear all list to free memory
    //     myJson.iteratorEnd();

    //     /*
    // The result of the above code

    // 0, Type: object, Key: food, Value: salad
    // 1, Type: object, Key: sweet, Value: cake
    // 2, Type: object, Key: appetizer, Value: snack

    // */
}

FirebaseJson EasyFirebase::readJson(const String &path)
{
    if (Firebase.getJSON(fbdo, path))
        return fbdo.jsonObject();
    else
        printError();
    return FirebaseJson();
}

bool EasyFirebase::hasJson(const String &path)
{
    return Firebase.getJSON(fbdo, path);
}

void EasyFirebase::writeJson(const String &path, FirebaseJson data)
{
    if (Firebase.setJSON(fbdo, path, data))
        printSuccess();
    else
        printError();
}

FirebaseJsonArray EasyFirebase::readJsonArray(const String &path) {
    if (Firebase.get(fbdo, path))
        return fbdo.jsonArray();
    else
        printError();
    return FirebaseJsonArray();
}

bool EasyFirebase::hasJsonArray(const String &path) {
    return Firebase.getArray(fbdo, path);
}

void EasyFirebase::writeJsonArray(const String &path, FirebaseJsonArray data) {
    if (Firebase.setArray(fbdo, path, data))
        printSuccess();
    else
        printError();
}