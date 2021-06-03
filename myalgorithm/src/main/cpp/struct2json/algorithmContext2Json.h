//
// Created by l.tan on 2021/6/3.
//

#ifndef MYMODULESAPP_ALGORITHMCONTEXT2JSON_H
#define MYMODULESAPP_ALGORITHMCONTEXT2JSON_H

#include "cJSON/cJSON.h"
#include "../algorithm/header/cgm_algorithm.h"
#include "inc/s2j.h"

cJSON *struct_to_json(jni_algorithm_context_t* struct_obj);
jni_algorithm_context_t *json_to_struct(cJSON* json_obj);
#endif //MYMODULESAPP_ALGORITHMCONTEXT2JSON_H
