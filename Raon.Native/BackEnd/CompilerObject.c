#include "CompilerObject.h"

#include "Utility/Converter.h"
#include "Utility/Error.h"

FCompilerObject *CreateCompilerObject() {
    FCompilerObject *object = malloc(sizeof(FCompilerObject));

    object->constants = NULL;
    object->codes = NULL;

    return object;
}

void FreeCompilerObject(FCompilerObject *object) {
    if (object == NULL) {
        return;
    }

    ARRAY_FREE(object->codes);
}

int64_t AppendDoubleConstant(FCompilerObject *object, double constant) {
    int64_t index = ARRAY_SIZE(object->constants);

    FValue value = { VALUE_DOUBLE, constant };
    ARRAY_PUSH(object->constants, value);

    return index;
}

int64_t AppendStringConstant(FCompilerObject *object, FString *constant) {
    int64_t index = ARRAY_SIZE(object->constants);

    FValue value = { VALUE_STRING, constant };
    ARRAY_PUSH(object->constants, value);

    return index;
}

void SerializeObject(FCompilerObject *object, char **out) {}

bool DeserializeObject(FCompilerObject *object, char *in) {}
