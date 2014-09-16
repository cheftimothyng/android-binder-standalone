
#include "stdio.h"
#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h> 


typedef unsigned int matrix_ringbuf_handle;


/*��װ��Client�Ĵ���*/
namespace android  
{  
    class RingBufClient  
    {  
    public:  

         RingBufClient *Instance() {
			return this;
        }
	
        unsigned int rpc_matrix_ringbuf_in(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size){
			Parcel  data ,reply;
			getZPService(); 
        	printf("client - binder->transact() \n");  
			data.writeInt32(handle);
			data.writeInt32(size);
			data.write(buf,size);
        	binder->transact(0, data, &reply);  
			return reply.readInt32();
		}

	  
	  unsigned int rpc_matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf)
	  {
	  	Parcel data, reply;
	  	getZPService();  
		data.writeInt32(handle);
		binder->transact(1, data, &reply); 
		*buf = (const unsigned char *)reply.readInt32();
		return reply.readInt32();
	  }

	  unsigned int rpc_matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size)
	  {
		Parcel data, reply;
		getZPService();  
		data.writeInt32(handle);
		data.writeInt32(size);
		binder->transact(2, data, &reply);  
		return reply.readInt32();
	  }
	  
    private:
         void getZPService(){
			 sp<IServiceManager> sm = defaultServiceManager();  
        	binder = sm->getService(String16("zp.svc"));  
        	printf("client - etService: %p\n", sm.get());  
        	if(binder == 0)  
        	{  
            	printf("ZPService not published, waiting...");  
            	return;  
        	}  
        }
		sp<IBinder> binder; 
		Parcel mem_t;
		Parcel::WritableBlob Blob;
    };  

 } 


unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle,const unsigned char *buf, unsigned int size)
{
	RingBufClient::Instance().rpc_matrix_ringbuf_in(handle,data,DATA_SIZE);
}

static unsigned char s_buff[128];
unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf)
{
}

/**
 @brief  ȷ�ϴ�����size���ֽڵ����ݣ�ֱ����ǰ�ƶ���ָ��size ���ֽڡ�

������matrix_ringbuf_aquireOut() ���ʹ�ã�ʹ��matrix_ringbuf_aquireOut ��ȡ������ָ�룬����������
���д����Ժ��������øú��������ָ�벻�ᷢ���ƶ�����ͬû�ж����ݽ��д���

 @param[in] handle �����������
 @param[in] size ��ɴ�������ݵĳ��ȡ�
 @return ����ȷ�ϴ���������ݳ��ȡ�����ָ����ǰ�ƶ����ֽ���Ŀ��
 @note     
 */
unsigned int matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size)
{
}



using namespace android; 

#define DATA_SIZE  1024

void write_buf(unsigned char *xxx)
{
	int i;
	for(i = 0 ;i < DATA_SIZE;i++)
		*(xxx + i) = i;
}

void dump_buf(unsigned char *xxx)
{
	int i ;
	printf("\nCliend :");
	for(i = 0 ;i < 500;i++){
		if(i%16 == 0)
			printf("\n");

		printf("%d   ",*(xxx + i));
	}
		printf("\n");
}


/*main function of server*/
int main(int arg, char** argv)  
{
	
    RingBufClient client();
	int len;
	printf("\n======================== testringbuf_client start ========================\n");
	matrix_ringbuf_handle handle = 0x12345678;

	//test 3.1
	unsigned char data[DATA_SIZE];
	memset(data,12,sizeof(data));
	client.rpc_matrix_ringbuf_in(handle,data,DATA_SIZE);

	//test 3.2
	const unsigned char *buf = NULL:
	int len = client.rpc_matrix_ringbuf_aquireOut( handle,&buf);
	memset(buf,34,len);
	client.rpc_matrix_ringbuf_confirmAquireOut(handle,DATA_SIZE,len);
	printf("\nCliend - len :%d\n",len);
	return 0;
}

