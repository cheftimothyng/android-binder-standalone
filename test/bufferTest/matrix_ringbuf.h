#ifndef __MATRIX_RINGBUF_H__
#define __MATRIX_RINGBUF_H__

#include <stdio.h>
#include <stdlib.h>

/*
 * ���λ�����
 * ���ƣ�ֻ����һ�����̣߳�һ��д�̶߳Ի��λ��������в���������
 * �ص㣺�������ƣ�KFIFO��ȡ�汾���ṩ1�ο�����0�ο�����
 * ʹ�ã���ο�unitTest �е�ringbuf����������
 */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 @brief ���λ����������ľ��
 */
typedef void* matrix_ringbuf_handle;


/**
 @brief ��ʼ��һ�����λ�����

 @param[in] bufsize 	��������С��������2��n���ݡ�
 @return 				�ɹ����� �����������ʧ�ܷ���С��0  ��ֵ��
 @note 
 */
matrix_ringbuf_handle matrix_ringbuf_init(unsigned int bufsize);



/**
 @brief ��ʼ��һ�����λ��������������ϲ����buffer�İ汾��
 */
matrix_ringbuf_handle matrix_ringbuf_initwithbuffer(void* ptr,unsigned int bufsize);


/**
 @brief д������

 @param[in] handle 	�����������
 @param[in] buf		��д������ݵĻ�����ָ�롣
 @param[in] size		��д�����ݵĳ��ȡ�
 @return 				���سɹ�д��������ֽ��������δд���κ����ݣ����ֵΪ0��
 */
unsigned int matrix_ringbuf_in(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size);


/**
 @brief ��ȡ����

 @param[in] handle 	�����������
 @param[out] buf		�ⲿ�ṩһ���洢���ݵĻ�����
 @param[in] size		����ȡ���ݵĳ��ȡ�
 @return 				���سɹ���ȡ�������ֽ��������δ�����κ����ݣ����ֵΪ0��
 @note ����һ�ο������ɻ��λ������������û��ṩ��buf  �С�
 */
unsigned int matrix_ringbuf_out(matrix_ringbuf_handle handle, unsigned char *buf, unsigned int size);


/**
 @brief ����һ����Ч����

 @param[in] handle 	�����������
 @param[in] size		�����Ե����ݵ��ֽڳ��ȡ���ֱ���ƶ���ָ�룬����������ݣ���������д���
 @return 				���سɹ������������ֽ�����
 @note  ������λ������е���Ч���ݳ���С��size  ������������������ա�
 */
unsigned int matrix_ringbuf_skip(matrix_ringbuf_handle handle, unsigned int size);



/**
 @brief �ӻ��λ�������ȡ��ָ��һ�����ݵ�ָ�롣

��ȡ���ݵ�ָ��󣬿��� ͨ����ָ��ֱ�Ӵ���������ݣ�
���ʡȥ�˽����ݴӻ������ڿ��������Ĳ��衣�ú������ؿɹ�
����������ֽڳ��ȡ�������matrix_ringbuf_confirmAquireOut() һͬʹ�á�

 @param[in] handle 	�����������
 @param[out] buf		�ⲿ�ṩ��һ������ָ�룬���ڻ��Ŀ�����ݵĻ�����ָ�롣
 @return 				���ظ�ָ�봦���ɹ�����������ֽ�����
 @note   
 */
unsigned int matrix_ringbuf_aquireOut(matrix_ringbuf_handle handle,const unsigned char**buf);



/**
 @brief  ȷ�ϴ�����size���ֽڵ����ݣ�ֱ����ǰ�ƶ���ָ��size ���ֽڡ�

������matrix_ringbuf_aquireOut() ���ʹ�ã�ʹ��matrix_ringbuf_aquireOut ��ȡ������ָ�룬����������
���д����Ժ��������øú��������ָ�벻�ᷢ���ƶ�����ͬû�ж����ݽ��д���

 @param[in] handle 	�����������
 @param[in] size		��ɴ�������ݵĳ��ȡ�
 @return 				����ȷ�ϴ���������ݳ��ȡ�����ָ����ǰ�ƶ����ֽ���Ŀ��
 @note     
 */
unsigned int matrix_ringbuf_confirmAquireOut(matrix_ringbuf_handle handle, unsigned int size);






/**
 @brief �ӻ��λ������ڻ�ȡһ�ο��пռ�

ֱ�ӻ�ȡ��ָ���λ������ڲ���ָ�룬��˿���ֱ�ӽ�����д�뻷�λ������ڡ�
����������д��ʱ���û�buffer �и��Ƶ����λ�������һ�ο�����
������matrix_ringbuf_confirmAquireIn() һͬʹ�á�

 @param[in] handle 	�����������
 @param[out] buf		�ⲿ�ṩ��һ������ָ�룬���ڻ��һ��ָ�򻺳������в��ֵ�ָ�롣
 @return 				���ظ�ָ�봦���ɹ�ʹ�õĿ��пռ���ֽ���Ŀ��
 @note    
 */
unsigned int matrix_ringbuf_aquireIn(matrix_ringbuf_handle handle, unsigned char**buf);



/**
 @brief  ȷ��д��size���ֽڵ����ݣ�ֱ����ǰ�ƶ�дָ��size ���ֽڡ�

 ������matrix_ringbuf_aquireIn() ���ʹ�ã�ʹ��matrix_ringbuf_aquireIn ��ȡ�˿��пռ��ָ�룬
�ڶ���д�������Ժ��������øú�������дָ�벻�ᷢ���ƶ�����ͬû��д�����ݡ�

 @param[in] handle 	�����������
 @param[in] size		д��������ֽ���Ŀ��
 @return 				����ȷ�ϵ����ݳ��ȡ���дָ����ǰ�ƶ����ֽ���Ŀ��
 @note     
 */
unsigned int matrix_ringbuf_confirmAquireIn(matrix_ringbuf_handle handle, unsigned int size);



/**
 @brief ��ȡ����������Ч���ݳ��ȡ�

 @param[in] handle 	�����������
 @return 				������Ч�����ֽڳ��ȡ�
 @note  
 */
unsigned int matrix_ringbuf_getDataSize(matrix_ringbuf_handle handle);



/**
 @brief ��ȡ�������п��пռ�ĳ��ȡ�

 @param[in] handle 	�����������
 @return 				���ػ������п��пռ���ֽڳ��ȡ�
 @note  ��ע�⣬���дָ����ڶ�ָ�룬�Ҷ�ָ��λ��0�߽�֮��ʱ��
 @note  ���пռ䳤��Ϊsizeof(out-->end)  + sizeof(start--> in)
 */
unsigned int matrix_ringbuf_getFreeSize(matrix_ringbuf_handle handle);




/**
 @brief ֱ������ƶ���ָ��size ���ֽڡ�

 ��size���ֽڵ������Ǹոձ�������������ģ�
 ��������size ֵΪ0xFFFFFFFF �����ָ��ֱ�ӻ��Ƶ�������������ݵ���ǰ�ˣ�
 �ⲿ�����ݼ�����дָ�������ǣ�����δ���ǣ�����ȡ�����ǡ�

 @note ��������Ƿ��̰߳�ȫ�ģ�����һ���̶߳���һ���߳�ͬʱд��ʱ���ú������ܳ������ݴ���
 @note ʹ���������б�֤�̰߳�ȫ��

 @param[in] handle 	�����������
 @param[in] size		��ָ��ֱ���򷴷����ƶ����ֽڳ��ȣ������¶�ȡδ�����ǵľ����ݡ�
 @return 				���سɹ�ȡ�صľ����ݳ��ȣ��ⲿ��������δ�����ǡ�
 */
unsigned int matrix_ringbuf_rewind(matrix_ringbuf_handle handle, unsigned int size);





/**
 @brief ����һ�����λ�������ʹ��ع��ʼ��״̬���ýӿڲ����̰߳�ȫ�ġ�

 @param[in] handle 	�����������
 @return 				�ɹ����� MHAL_SUCCESS��ʧ�ܷ���С��0  ��ֵ��
 @note 
 */
int matrix_ringbuf_reset(matrix_ringbuf_handle handle);




/**
 @brief ע��һ�����λ����������ͷ���ռ䡣

 @param[in] handle 	�����������
 @return 				�ɹ����� MHAL_SUCCESS��ʧ�ܷ���С��0  ��ֵ��
 @note 
 */
int matrix_ringbuf_exit(matrix_ringbuf_handle handle) ;


#ifdef __cplusplus
}
#endif

#endif /* __MATRIX_RINGBUF_H__ */
