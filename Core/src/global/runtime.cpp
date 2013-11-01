/*
 * runtime.cpp
 *
 *  Created on: 16.01.2013
 *      Author: nonametr
 */
#include "runtime.h"
#include <stdio.h>

map<string, CRdtscll*> CRdtscll::static_calls   = create_static_calls_map();
map<string, call> CRdtscll::cnt_calls           = create_cnt_calls_map();
pthread_mutex_t CRdtscll::cnt_calls_lock    = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t CRdtscll::static_calls_lock = PTHREAD_MUTEX_INITIALIZER;

CRdtscll::~CRdtscll()
{
    unsigned long long val;
    rdtscll( val );
    if(val > t_start)
    {
        unsigned long long tics = val - t_start;

        pthread_mutex_lock(&cnt_calls_lock);
        cnt_calls[function_name].avrg_time = (unsigned long long)((cnt_calls[function_name].avrg_time + tics)>>1);
        pthread_mutex_unlock(&cnt_calls_lock);
        if(RDTSCLL_LVL == RDTSCLL_VERBOSE)
        {
            printf( "-->t:%llu:---%s(): dt:%llu<--\r\n", val, function_name.c_str(), (unsigned long long)(tics*0.00001f) );
        }
    }
}

CRdtscll::CRdtscll(const char* func_name) : function_name( func_name )
{
    if(RDTSCLL_LVL)
    {
        unsigned long long val;
        rdtscll( val );
        t_start = val;
        pthread_mutex_lock(&cnt_calls_lock);
        cnt_calls[function_name].num_calls++;
        pthread_mutex_unlock(&cnt_calls_lock);
    }
}

void CRdtscll::begin(const char *func_name, const int line)
{
    char buf[128];
    char func_name_uniq[128];//Possible data lost without func_name_uniq, when 2 threads calls same function!
    snprintf(func_name_uniq, 128, "%s:%u", func_name, pthread_self());
    if(line)
    {
        snprintf(buf, 128, "ln:%d:%s", line, func_name);
        pthread_mutex_lock(&static_calls_lock);
        static_calls[func_name_uniq] = new CRdtscll(buf);
        pthread_mutex_unlock(&static_calls_lock);
    }
    else
    {
        pthread_mutex_lock(&static_calls_lock);
        static_calls[func_name_uniq] = new CRdtscll(func_name);
        pthread_mutex_unlock(&static_calls_lock);
    }
}

void CRdtscll::end(const char *func_name)
{
    pthread_mutex_lock(&static_calls_lock);
    delete static_calls[func_name];
    pthread_mutex_unlock(&static_calls_lock);
}

string CRdtscll::print()
{
    string res;
    char buf[1024];
    pthread_mutex_lock(&cnt_calls_lock);
    for(map<string, call>::iterator call_it = cnt_calls.begin(); call_it != cnt_calls.end() ; call_it++)
    {
        snprintf(buf, 1024, "Method %-20s\t called %u times,\t average call time = %llu\r", call_it->first.c_str(), call_it->second.num_calls, call_it->second.avrg_time);
        res += buf;
    }
    pthread_mutex_unlock(&cnt_calls_lock);
    return res;
}
