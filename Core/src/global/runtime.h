/*
 * runtime.h
 *
 *  Created on: 16.01.2013
 *      Author: nonametr
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include <string>
#include <map>
#include <pthread.h>

using namespace std;

#define RDTSCLL_OFF 	0
#define RDTSCLL_ON 		2
#define RDTSCLL_VERBOSE 3

#define RDTSCLL_LVL RDTSCLL_VERBOSE

struct call
{
    unsigned int num_calls;
    unsigned long long avrg_time;
};

class CRdtscll
{
private:
    string function_name;
    unsigned long long	t_start;
    static pthread_mutex_t static_calls_lock, cnt_calls_lock;
    static map<string, call> cnt_calls;
    static map<string, CRdtscll*> static_calls;
    static map<string, CRdtscll*> create_static_calls_map()
    {
        map<string, CRdtscll*> init;
        return init;
    }
    static map<string, call> create_cnt_calls_map()
    {
        map<string, call> init;
        return init;
    }
public:
    static string print();
    static void begin(const char *func_name, const int line = 0);
    static void end(const char *func_name);
    CRdtscll( const char *func_name );
    ~CRdtscll();
};

#define rdtscll(val) __asm__ __volatile__("rdtsc" :"=A"(val))

#define RUNTIME()       CRdtscll __rt__( __FUNCTION__);
#define RUNTIME_BEGIN() CRdtscll::begin(__FUNCTION__, __LINE__);
#define RUNTIME_END()   CRdtscll::end(__FUNCTION__);
#define RUNTIME_BEGIN_SPEC(S) CRdtscll::begin(S);
#define RUNTIME_END_SPEC(S)   CRdtscll::end(S);


#endif /* RUNTIME_H_ */
