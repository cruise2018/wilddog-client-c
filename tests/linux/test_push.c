
#include <stdio.h>
#include <stdlib.h>

#include "wilddog_debug.h"
#include "wilddog.h"
#include "test.h"

STATIC void test_onPushFunc(u8 *p_path,void* arg, Wilddog_Return_T err)
{
						
	if(err < WILDDOG_HTTP_OK || err >= WILDDOG_HTTP_NOT_MODIFIED)
	{
		//wilddog_debug("push failed");
		
		TEST_RESULT_PRINTF("wilddog_push",TESTFUNCNAME_TABLECASE,TEST_ERR,err);
		return;
	}	
	else
		TEST_RESULT_PRINTF("wilddog_push",TESTFUNCNAME_TABLECASE,TEST_OK,0);
	//wilddog_debug("new path is %s", p_path);
	*(BOOL*)arg = TRUE;
	return;
}

int main(void)
{
	BOOL isFinish = FALSE;
	Wilddog_T wilddog;
	Wilddog_Node_T * p_node = NULL, *p_head = NULL;
	wilddog_init();

	p_head = wilddog_node_createObject(NULL);
	p_node = wilddog_node_createNum("2",1234);
	wilddog_node_add(p_head, p_node);
	
	wilddog = wilddog_new(TEST_URL);
	wilddog_push(wilddog, p_head, test_onPushFunc, (void *)&isFinish);	
	wilddog_node_delete(p_head);
	
	while(1)
	{
		if(isFinish)
		{
			//wilddog_debug("push success!");
			break;
		}
		wilddog_trySync();
	}
	wilddog_destroy(&wilddog);
}

