#include "json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
* Blocks off the public constructor
*
* @access private
*
*/
JSON::JSON()
{
}

/**
* Parses a complete JSON encoded string
*
* @access public
*
* @param char* data The JSON text
*
* @return JSONValue* Returns a JSON Value representing the root, or NULL on error
*/
JSONValue *JSON::parse(const char *data)
{
/// Skip any preceding whitespace, end of data = no JSON = fail
    if (!SkipWhitespace(&data))
        return NULL;

/// We need the start of a value here now...
    JSONValue *value = JSONValue::Parse(&data);
    if (value == NULL)
        return NULL;

/// Can be white space now and should be at the end of the string then...
    if (SkipWhitespace(&data))
    {
        delete value;
        return NULL;
    }

/// We're now at the end of the string
    return value;
}

/**
* Turns the passed in JSONValue into a JSON encode string
*
* @access public
*
* @param JSONValue* value The root value
*
* @return std::string Returns a JSON encoded string representation of the given value
*/
std::string JSON::stringify(const JSONValue *value)
{
    if (value != NULL)
        return value->stringify();
    else
        return "";
}

/**
* Skips over any whitespace characters (space, tab, \r or \n) defined by the JSON spec
*
* @access protected
*
* @param char** data Pointer to a char* that contains the JSON text
*
* @return bool Returns true if there is more data, or false if the end of the text was reached
*/
bool JSON::SkipWhitespace(const char **data)
{
    while (**data != 0 && (**data == ' ' || **data == '\t' || **data == '\r' || **data == '\n'))
        (*data)++;

    return **data != 0;
}

/**
* Extracts a JSON String as defined by the spec - "<some chars>"
* Any escaped characters are swapped out for their unescaped values
*
* @access protected
*
* @param char** data Pointer to a char* that contains the JSON text
* @param std::string& str Reference to a std::string to receive the extracted string
*
* @return bool Returns true on success, false on failure
*/
bool JSON::ExtractString(const char **data, std::string &str, bool default_end)
{
    str = "";

    while (**data != 0)
    {
/// Save the char so we can change it if need be
        char next_char = **data;

/// Escaping something?
        if (next_char == '\\')
        {
/// Move over the escape char
            (*data)++;

/// Deal with the escaped char
            switch (**data)
            {
            case '"':
                next_char = '"';
                break;
            case '\\':
                next_char = '\\';
                break;
            case '/':
                next_char = '/';
                break;
            case 'b':
                next_char = '\b';
                break;
            case 'f':
                next_char = '\f';
                break;
            case 'n':
                next_char = '\n';
                break;
            case 'r':
                next_char = '\r';
                break;
            case 't':
                next_char = '\t';
                break;
//             case 'u':
//             {
/// We need 5 chars (4 hex + the 'u') or its not valid
//                 if (!simplejson_wcsnlen(*data, 5))
//                     return false;

/// Deal with the chars
//                 next_char = 0;
//                 for (int i = 0; i < 4; i++)
//                 {
/// Do it first to move off the 'u' and leave us on the
/// final hex digit as we move on by one later on
//                     (*data)++;
// 
//                     next_char <<= 4;

/// Parse the hex digit
//                     if (**data >= '0' && **data <= '9')
//                         next_char |= (**data - '0');
//                     else if (**data >= 'A' && **data <= 'F')
//                         next_char |= (10 + (**data - 'A'));
//                     else if (**data >= 'a' && **data <= 'f')
//                         next_char |= (10 + (**data - 'a'));
//                     else
//                     {
/// Invalid hex digit = invalid JSON
//                         return false;
//                     }
//                 }
//                 break;
//             }

/// By the spec, only the above cases are allowed
            default:
                return false;
            }
        }

/// End of the string?
        else if (next_char == '"')
        {
            (*data)++;
            str.reserve(); // Remove unused capacity
            return true;
        }
        ///Other end of the string
        else if(default_end == false)
	{
	    if (next_char == ':')
	    {
		str.reserve(); // Remove unused capacity
		return true;
	    }
	}

/// Disallowed char?
//         else if (next_char < ' ' && next_char != '\t')
//         {
/// SPEC Violation: Allow tabs due to real world cases
//             return false;
//         }

/// Add the next char
        str += next_char;

/// Move on
        (*data)++;
    }

/// If we're here, the string ended incorrectly
    return false;
}

/**
* Parses some text as though it is an integer
*
* @access protected
*
* @param char** data Pointer to a char* that contains the JSON text
*
* @return double Returns the double value of the number found
*/
double JSON::ParseInt(const char **data)
{
    double integer = 0;
    while (**data != 0 && **data >= '0' && **data <= '9')
        integer = integer * 10 + (*(*data)++ - '0');

    return integer;
}

/**
* Parses some text as though it is a decimal
*
* @access protected
*
* @param char** data Pointer to a char* that contains the JSON text
*
* @return double Returns the double value of the decimal found
*/
double JSON::ParseDecimal(const char **data)
{
    double decimal = 0.0;
    double factor = 0.1;
    while (**data != 0 && **data >= '0' && **data <= '9')
    {
        int digit = (*(*data)++ - '0');
        decimal = decimal + digit * factor;
        factor *= 0.1;
    }
    return decimal;
}

