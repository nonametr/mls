#ifndef VALUE_H
#define VALUE_H

#include "json.h"
#include "json_value.h"
#include "global.h"

class Value
{
public:
	inline int &toInt()				{ return var.i_val;  }
	inline unsigned int &toUInt()	{ return var.ui_val; }
	inline long long &toLLong()		{ return var.ll_val; }
	inline char &toChar()			{ return var.c_val;  }
	inline unsigned char &toUChar()  { return var.uc_val; }
	inline float &toFloat()		{ return (float&)var.d_val;  }
	inline double &toDouble()		{ return var.d_val;  }
	inline bool &toBool()			{ return var.b_val;  }
	Value()					{	memset(&var, 0, sizeof(var)); }
	Value(int v_v)			{	load(v_v); type = INT; }
	Value(unsigned int v_v)	{	load(v_v); type = UINT; }
	Value(long long v_v)	{	load(v_v); type = LLONG; }
	Value(unsigned long long v_v) {	load(v_v); type = ULLONG; }
	Value(char v_v)			{	load(v_v); type = CHAR; }
	Value(unsigned char v_v){	load(v_v); type = UCHAR; }
	Value(float v_v)		{	load(v_v); type = FLOAT; }
	Value(double v_v)		{	load(v_v); type = DOUBLE; }
	Value(bool v_v)			{	load(v_v); type = BOOL; }
private:
	enum Type { INT, UINT, LLONG, ULLONG, CHAR, UCHAR, FLOAT, DOUBLE, BOOL, MAX } type;
	template<class T> inline void load(T v)
	{
		memset(&var, 0, sizeof(var));
		memcpy(&var, &v, sizeof(T));
	}
	union
	{
		int i_val;
		unsigned int ui_val;
		long long ll_val;
		unsigned long long ull_val;
		char c_val;
		unsigned char uc_val;
		bool b_val;
		double d_val;
	} var;
};

#endif
