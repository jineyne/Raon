#include "Location.h"

FLocation *CreateLocation(FString *source, FToken *token) {
    FLocation *location = malloc(sizeof(FLocation));
    location->source = CopyString(source);
    location->token = token;
    return location;
}

void FreeLocation(FLocation *location) {
    FreeString(location->source);
    FreeToken(location->token);

    free(location);
}
