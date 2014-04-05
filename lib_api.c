#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,val=-1,ch,no_domains;
    char name[50];
    int *act_domains;
    virConnectPtr con_ptr;
    virDomainPtr dom_ptr;

    con_ptr = virConnectOpen("xen:///");

    if (con_ptr == NULL) {
        fprintf(stderr, "Error opening connection to XEN:///  \n");
        return 1;
    }
    else
    {
        no_domains=virConnectNumOfDomains(con_ptr);
        act_domains=malloc(sizeof(int) * no_domains);
        no_domains = virConnectListDomains(con_ptr, act_domains, no_domains);
        free(act_domains);

        while(1)
        {
            
            printf("1.Start\n2.Suspend\n3.Resume\n4.Shutdown\n5.exit ");
            scanf("%d",&ch);

            printf("\n Enter Active Domian name ");
            scanf("%s",&name);
  
            dom_ptr=virDomainLookupByName(con_ptr,name);
        
            switch(ch)
            {
                case 1:
		       val=virDomainCreate(dom_ptr);
                       if(val==0)      
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 2:
		       val=virDomainSuspend(dom_ptr);
                       if(val==0)
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 3:
		        val=virDomainResume(dom_ptr);
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;

                case 4:
			val=virDomainShutdown(dom_ptr);
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;
                default:exit(1);
            }
        }
        virConnectClose(con_ptr);
    }
}
