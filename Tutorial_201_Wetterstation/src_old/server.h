#include <Arduino.h>

void replyOK();

void replyOKWithMsg(String);

void replyNotFound(String);

void replyBadRequest(String);

void replyServerError(String);

void handleNotFound();

void handleGetEdit();

String checkForUnsupportedPath(String);

void handleStatus();

void handleFileList();

bool handleFileRead(String);

String lastExistingParent(String);

void handleFileCreate();

void deleteRecursive(String);

void handleFileDelete();

void handleFileUpload();

void serverInit();

void handleClient();