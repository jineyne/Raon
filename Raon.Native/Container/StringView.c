#include "StringView.h"

FStringView CreateStringView(u16 *data, size_t length) {
    FStringView view = {0, NULL};

    view.length = length;
    view.data = data;

    return view;
}

FStringView CreateStringViewFromCStr(u16 *data) {
    return CreateStringView(data, u16len(data));
}

FStringView TrimLeftStringView(FStringView view) {
    size_t i = 0;
    while (i < view.length && u16isspace(view.data[i])) {
        i += 1;
    }

    return CreateStringView(view.data + i, view.length - i);
}

FStringView TrimRightStringView(FStringView view) {
    size_t i = 0;
    while (i < view.length && u16isspace(view.data[view.length - 1 - i])) {
        i += 1;
    }

    return CreateStringView(view.data, view.length - i);
}

FStringView TrimStringView(FStringView view) {
    return TrimRightStringView(TrimLeftStringView(view));
}

bool IndexOfStringView(FStringView view, u16 c, size_t *index) {
    size_t i = 0;
    while (i < view.length && view.data[i] != c) {
        i += 1;
    }

    if (i < view.length) {
        if (index) {
            *index = i;
        }
        return true;
    } else {
        return false;
    }
}

FStringView ChopLeftStringView(FStringView *view, size_t size) {
    if (size > view->length) {
        size = view->length;
    }

    FStringView result = CreateStringView(view->data, size);

    view->data += size;
    view->length -= size;

    return result;
}

FStringView ChopRightStringView(FStringView *view, size_t size) {
    if (size > view->length) {
        size = view->length;
    }

    FStringView result = CreateStringView(view->data + view->length - size, size);

    view->length -= size;

    return result;
}

bool TryChopByDelimStringView(FStringView *view, u16 delim, FStringView *chunk) {
    size_t i = 0;
    while (i < view->length && view->data[i] != delim) {
        i += 1;
    }

    FStringView result = CreateStringView(view->data, i);

    if (i < view->length) {
        view->length -= i + 1;
        view->data += i + 1;
        if (chunk) {
            *chunk = result;
        }
        return true;
    }

    return false;
}

FStringView ChopByDelimStringView(FStringView *view, u16 delim) {
    size_t i = 0;
    while (i < view->length && view->data[i] != delim) {
        i += 1;
    }

    FStringView result = CreateStringView(view->data, i);

    if (i < view->length) {
        view->length -= i + 1;
        view->data += i + 1;
    } else {
        view->length -= i;
        view->data += i;
    }

    return result;
}

FStringView StringViewChopByStringView(FStringView *view, FStringView delim) {
    FStringView window = CreateStringView(view->data, delim.length);
    size_t i = 0;
    while (i + delim.length < view->length 
        && !(CompareStringView(window, delim))) 
    {
        i++;
        window.data++;
    }

    FStringView result = CreateStringView(view->data, i);

    if (i + delim.length == view->length) {
        // include last <thicc_delim.count> characters if they aren't 
        //  equal to thicc_delim
        result.length += delim.length; 
    }
    
    // Chop!
    view->data  += i + delim.length;
    view->length -= i + delim.length;

    return result;
}

bool StringViewStartWith(FStringView view, FStringView prefix) {
     if (prefix.length <= view.length) {
        FStringView actual_prefix = CreateStringView(view.data, prefix.length);
        return CompareStringView(prefix, actual_prefix);
    }

    return false;
}

bool StringViewEndWith(FStringView view, FStringView suffix) {
    if (suffix.length <= view.length) {
        FStringView actual_suffix = CreateStringView(view.data + view.length - suffix.length, suffix.length);
        return CompareStringView(suffix, actual_suffix);
    }

    return false;
}


int CompareStringView(FStringView lhs, FStringView rhs) {
    if (lhs.length == rhs.length) {
        return memcmp(lhs.data, rhs.data, lhs.length);
    } else if (lhs.length > rhs.length) {
        return -1;
    } else if (lhs.length < rhs.length) {
        return 1;
    }
}
