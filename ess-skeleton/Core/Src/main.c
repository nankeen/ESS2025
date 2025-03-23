/* Includes */
#include "main.h"
#include "ess_helper.h"

int main(void)
{
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();


    while(1)
    {
    }
}
