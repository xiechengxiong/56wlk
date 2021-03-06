/////////////////////////////////////////////////////////////////////////////

/** 
 * @file        ub_conf.h
 * @brief       header file of ub_conf.h
 * 
 */

#ifndef __UB_CONF_H__
#define __UB_CONF_H__

#include "ul_conf.h"

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

#define UB_CONF_SUCCESS 0								  /**< 获取配置成功*/
#define UB_CONF_DEFAULT -1								  /**< 找不到相应的配置项，如果有默认值的话使用默认值*/
#define UB_CONF_LOADFAIL -2									/**< 获取失败　*/
#define UB_CONF_OVERFLOW -3									/**< 数值型超出表示范围 */
#define UB_CONF_INVALID_CHARACTER -4						/**< 数值型中有无效字符 */
#define UB_CONF_LOST -5										/**< 找不到配置项*/
#define UB_CONF_CHECKSUCCESS -6								/**< 检查格式成功*/
#define UB_CONF_CHECKFAIL -7								/**< 格式不对,检查失败*/
#define UB_CONF_SETMULTIPLE -8								/**< 相同的项出现超过一次*/
#define UB_CONF_NULL -9											

#define UB_CONF_MAX_CLONE 4

#define UB_CONF_DEFAULT_ITEMNUM 1024 
#define UB_CONF_IPMAX (UB_CONF_DEFAULT_ITEMNUM/8)
#define UB_CONF_IPLENMAX 16

#define UB_CONF_READCONF 0


typedef struct _ub_conf_data_t {
	Ul_confdata	*option;      								/**< 配置项数据*/
	Ul_confdata	*range;       								/**< range文件里的配置项,文件不存在值为空 */
	char		filename[LINE_SIZE]; 						/**< 配置文件名 */
	FILE		*conf_file;									/**< 配置文件句柄*/
	int			build;                						/**< 需要创建文件,0读取配置 >0 创建配置文件 */
} ub_conf_data_t;


typedef struct _ub_svr_ip_t {
	u_int 			num;  									/**< 同一台机器的IP数，处理clone IP */	
	char 			name[UB_CONF_MAX_CLONE][WORD_SIZE];  	/**< 用 / 分隔的同一机器的IP放在一起*/
} ub_svr_ip_t;


typedef struct _ub_svr_t {									/**< 服务器提供服务的配置*/
	char				svr_name[WORD_SIZE];				/**< 服务名*/
	u_int				port;                               /**< 提供服务的端口 */
	u_int				read_timeout;                       /**< 读超时　*/
	u_int				write_timeout;                      /**< 写超时 */
	u_int				thread_num;                         /**< 线程数 */
	u_int				connect_type;                       /**< 连接类型　0短连接　非0长连接 */
	u_int				server_type;						/**< 使用的pool类型,参照ub_server的设置 */
	u_int				queue_size;							/**< 队列缓冲长度，在pool类型为cpool时,服务设置中有效*/
	u_int				sock_size;							/**< sock缓冲长度, 在pool类型为cpool时,服务设置中有效*/
} ub_svr_t;                              	


typedef struct _ub_request_svr_t {							/**< 请求服务的配置*/
	char				svr_name[WORD_SIZE];				/**< 服务名*/
	u_int				num;								/**< ip地址的个数 */
	ub_svr_ip_t			ip_list[UB_CONF_IPMAX];				/**< ip 地址信息 */
	u_int				port;                               /**< 端口 */
	u_int				read_timeout;                       /**< 读超时　*/
	u_int				write_timeout;                      /**< 写超时 */
	u_int				connect_timeout;                    /**< 连接超时 */
	u_int				max_connect;                        /**< 最大连接数 */
	u_int				retry;                              /**< 重试次数　*/
	u_int				connect_type;                       /**< 连接类型　0短连接　非0长连接 */
	u_int               linger;	    /**< 是否使用linger方式       */
} ub_request_svr_t;                              	


/**
 * @brief 初始化配置文件结构
 *
 * @param path 文件路径
 * @param filename 文件名
 * @param build == UB_CONF_READCONF 读取配置文件， != UB_CONF_READCONF生成样例配置文件，默认为读取
 * @param num 配置条目数，默认为1024
 * @return NULL失败，否则为配置文件结构指针
 */ 
ub_conf_data_t * ub_conf_init(const char *path, const char *filename, 
		const int build = UB_CONF_READCONF, const int num = UB_CONF_DEFAULT_ITEMNUM); 


/**
 * @brief 释放配置文件结构
 *
 * @param conf 结构指针
 * @return UB_CONF_SUCCESS总是成功
 */ 
int ub_conf_close(ub_conf_data_t *conf);


/**
 * @brief 在配置信息结构中读取配置项的值，并通过range文件进行检查，带缓冲区长度限制,值为char*类型
 *
 * @param conf 结构指针
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param n 读取的最大长度
 * @param comment 配置项的说明，写配置文件用
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 
int ub_conf_getnstr(const ub_conf_data_t *conf, const char *conf_name,
		char *conf_value,  const size_t n, const char *comment,  const char * default_value=NULL); 


/**
 * @brief 在配置信息结构中读取配置项的值，并通过range文件进行检查，其值int类型
 *
 * @param conf 结构指针
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 
int ub_conf_getint(const ub_conf_data_t *conf, const char *conf_name, int *conf_value,  
		const char *comment,  const int * default_value=NULL); 


/**
 * @brief 在配置信息结构中读取配置项的值，并通过range文件进行检查，其值unsigned int类型
 *
 * @param conf 结构指针
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getuint(const ub_conf_data_t *conf, const char *conf_name, 
		unsigned int *conf_value,  const char *comment, const unsigned int *default_value=NULL);

/**
 * @brief 在配置信息结构中读取配置项的值，并通过range文件进行检查，其值long long类型
 *
 * @param conf 结构指针
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getint64(const ub_conf_data_t *conf, const char *conf_name, 
		long long *conf_value,  const char *comment, const long long *default_value=NULL);


/**
 * @brief 在配置信息结构中读取配置项的值，并通过range文件进行检查，其值unsigned long long类型
 *
 * @param conf 结构指针
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 



int ub_conf_getuint64(const ub_conf_data_t *conf, const char *conf_name, 
		unsigned long long *conf_value, const char *comment, const unsigned long long *default_value=NULL);

/**
 * @brief 在配置信息结构中读取配置项的值，并通过range文件进行检查，其值float类型
 *
 * @param conf 结构指针
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 



int ub_conf_getfloat(const ub_conf_data_t *conf, const char *conf_name, 
		float *conf_value, const char *comment, const float *default_value=NULL);



/**
 * @brief 在配置信息结构中读取服务器配置项的值，并通过range文件进行检查，其值为ub_svr_t类型
 * 
 * ub_svr_t类型的配置由多行配置项组成，range需要一个一个的进行设置，ub_svr_t不支持默认值
 * @param conf 结构指针
 * @param product_name 产品名，可以用NULL代替
 * @param module_name 模块名, 不可以传入NULL
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符(针对端口和超时设置)
 * - UB_CONF_LOST 没有找到配置项(多个配置有一个缺失就会返回)
 * - UB_CONF_CHECKFAIL range文件检查失败(多个配置有一个失败就会返回)
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getsvr(const ub_conf_data_t *conf, const char *product_name, 
		const char *module_name, ub_svr_t *conf_value, const char *comment); 


/**
 * @brief 在配置信息结构中读取请求服务配置项的值，并通过range文件进行检查，其值为ub_reqsvr_t类型
 * ub_reqsvr_t类型的配置由多行配置项组成，range需要一个一个的进行设置，ub_reqsvr_t不支持默认值
 * @param conf 结构指针
 * @param product_name 产品名，可以用NULL代替
 * @param module_name 模块名, 不可以传入NULL
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符(针对端口和超时设置)
 * - UB_CONF_LOST 没有找到配置项(多个配置有一个缺失就会返回)
 * - UB_CONF_CHECKFAIL range文件检查失败(多个配置有一个失败就会返回)
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getreqsvr(const ub_conf_data_t *conf, const char *c_name,
		const char *module_name, ub_request_svr_t *conf_value, const char *comment);

/**
 * @brief 从配置文件中一次读取一个配置项的值，并通过range文件进行检查，带缓冲区长度限制,值为char*类型
 * 不支持生成样例配置文件
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param n 读取的最大长度
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getonenstr(const char *path, const char *filename, 
		const char *conf_name, char *conf_value, const size_t n,  const char *default_value = NULL);


/**
 * @brief 从配置文件中一次读取一个配置项的值，并通过range文件进行检查,其值为int类型
 * 不支持生成样例
 
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getoneint (const char *path, const char *filename, 
		const char *conf_name, int *conf_value, const int *default_value = NULL);


/**
 * @brief 从配置文件中一次读取一个配置项的值，并通过range文件进行检查，其值为unsigned int类型
 * 不支持生成样例
 *
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getoneuint(const char *path, const char *filename, 
		const char *conf_name, unsigned int *conf_value, const unsigned  int *default_value = NULL );

/**
 * @brief 从配置文件中一次读取一个配置项的值，并通过range文件进行检查，其值为long long 类型
 * 不支持生成样例
 *
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 


int ub_conf_getoneint64(const char *path, const char *filename, 
		const char *conf_name, long long *conf_value, const long long *default_value = NULL);


/**
 * @brief 从配置文件中一次读取一个配置项的值，并通过range文件进行检查，其值为unsigned long long 类型
 * 不支持生成样例
 *
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getoneuint64(const char *path, const char *filename, 
		const char *conf_name, unsigned long long *conf_value, const unsigned long long *default_value = NULL);

/**
 * @brief 从配置文件中一次读取一个配置项的值，并通过range文件进行检查，其值为float 类型
 * 不支持生成样例
 *
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf_name 配置项名
 * @param[out] conf_value 配置项的值
 * @param default_value 配置项在配置文件里找不到时的默认值，默认情况下为NULL，即不使用默认值
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_DEFAULT 获取失败，使用默认值
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符
 * - UB_CONF_LOST 没有找到配置项
 * - UB_CONF_CHECKFAIL range文件检查失败
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 

int ub_conf_getonefloat(const char *path, const char *filename, 
		const char *conf_name, float *conf_value, const float *default_value = NULL);



/**
 * @brief 从配置文件中只读取一个服务器配置项的值，并通过range文件进行检查
 * 
 * ub_svr_t类型的配置由多行配置项组成，range需要一个一个的进行设置，ub_svr_t不支持默认值
 *
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param product_name 产品名，可以用NULL代替
 * @param module_name 模块名, 不可以传入NULL
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符(针对端口和超时设置)
 * - UB_CONF_LOST 没有找到配置项(多个配置有一个缺失就会返回)
 * - UB_CONF_CHECKFAIL range文件检查失败(多个配置有一个失败就会返回)
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 


int ub_conf_getonesvr(const char *path, const char *filename, const char *product_name, 
		const char *module_name, ub_svr_t *conf_value);

/**
 * @brief 从配置文件中只读取一个读取请求服务配置项的值，并通过range文件进行检查，其值为ub_reqsvr_t类型
 * 
 * ub_reqsvr_t类型的配置由多行配置项组成，range需要一个一个的进行设置，ub_reqsvr_t不支持默认值
 *
 * @param path 配置文件路径
 * @param filename 配置文件名
 * @param conf 结构指针
 * @param product_name 产品名，可以用NULL代替
 * @param module_name 模块名, 不可以传入NULL
 * @param[out] conf_value 配置项的值
 * @param comment 配置项的说明，写配置文件用
 * @return
 * - UB_CONF_SUCCESS 获取成功
 * - UB_CONF_OVERFLOW 数值类型溢出
 * - UB_CONF_INVALID_CHARACTER 出现非法字符(针对端口和超时设置)
 * - UB_CONF_LOST 没有找到配置项(多个配置有一个缺失就会返回)
 * - UB_CONF_CHECKFAIL range文件检查失败(多个配置有一个失败就会返回)
 * - UB_CONF_SETMULTIPLE 配置项重复出现
 * - UB_CONF_NULL 输入参数非法
 **/ 


int ub_conf_getonereqsvr(const char *path, const char *filename, const char *product_name, 
		const char *module_name, ub_request_svr_t *conf_value);

/**
 * @brief 用宏封装的获取配置函数,获取失败立刻结束程序, 出错信息参考日志文件
 *
 */


#define UB_CONF_GETNSTR(conf, conf_name, n, conf_value, comment) do {\
	if (ub_conf_getnstr(conf, conf_name, n, conf_value, comment) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0) 


#define UB_CONF_GETINT(conf, conf_name, conf_value, comment) do {\
	if (ub_conf_getint(conf, conf_name, conf_value,comment) != UB_CONF_SUCCESS) { \
		exit(1); \
	} \
}while(0)

#define UB_CONF_GETUINT(conf, conf_name, conf_value, comment) do {\
	if (ub_conf_getuint(conf, conf_name, conf_value,comment) != UB_CONF_SUCCESS) { \
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETINT64(conf, conf_name, conf_value, comment) do {\
	if (ub_conf_getint64(conf, conf_name, conf_value,comment) != UB_CONF_SUCCESS) { \
	exit(1); \
} \
}while(0)



#define UB_CONF_GETUINT64(conf, conf_name, conf_value, comment) do {\
	if (ub_conf_getuint64(conf, conf_name, conf_value,comment) != UB_CONF_SUCCESS) { \
	exit(1); \
} \
}while(0)

#define UB_CONF_GETFLOAT(conf, conf_name, conf_value, comment) do {\
	if (ub_conf_getfloat(conf, conf_name, conf_value,comment) != UB_CONF_SUCCESS) { \
	exit(1); \
} \
}while(0)


#define UB_CONF_GETSVR(conf, product_name, module_name, conf_value, comment) do {\
	if (ub_conf_getsvr(conf, product_name, module_name, conf_value, comment) != UB_CONF_SUCCESS) {\
		exit(1);\
	} \
}while(0)

#define UB_CONF_GETREQSVR(conf, product_name, module_name, conf_value, comment) do {\
	if (ub_conf_getreqsvr(conf, product_name, module_name, conf_value, comment) != UB_CONF_SUCCESS) {\
		exit(1);\
	} \
}while(0)

/**
 * @brief 带_DEFAULT后缀,可设置默认值
 */
#define UB_CONF_GETNSTR_DEFAULT(conf, conf_name, conf_value, n, comment, default_value) do {\
	int ret = ub_conf_getnstr(conf, conf_name, conf_value, n, comment, default_value); \
	if (ret != UB_CONF_SUCCESS && ret != UB_CONF_DEFAULT) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETINT_DEFAULT(conf, conf_name, conf_value, comment, default_value) do {\
	int default_int_value = (default_value);\
	int ret = ub_conf_getint(conf, conf_name, conf_value,comment, &default_int_value);\
	if (ret != UB_CONF_SUCCESS && ret != UB_CONF_DEFAULT) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETUINT_DEFAULT(conf, conf_name, conf_value, comment, default_value) do {\
	unsigned int default_uint_value = (default_value);\
	int ret = ub_conf_getuint(conf, conf_name, conf_value, comment, &default_uint_value);\
	if (ret != UB_CONF_SUCCESS && ret != UB_CONF_DEFAULT) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETINT64_DEFAULT(conf, conf_name, conf_value, comment, default_value) do {\
	long long default_int64_value = (default_value);\
	int ret = ub_conf_getint64(conf, conf_name, conf_value,comment, &default_int64_value);\
	if (ret != UB_CONF_SUCCESS && ret != UB_CONF_DEFAULT) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETUINT64_DEFAULT(conf, conf_name, conf_value, comment, default_value) do {\
	unsigned long long default_uint64_value = (default_value);\
	int ret = ub_conf_getuint64(conf, conf_name, conf_value, comment, &default_uint64_value);\
	if (ret != UB_CONF_SUCCESS && ret != UB_CONF_DEFAULT) {\
		exit(1); \
	} \
}while(0)

#define UB_CONF_GETFLOAT_DEFAULT(conf, conf_name, conf_value, comment, default_value) do {\
	float default_float_value = (default_value);\
	int ret = ub_conf_getfloat(conf, conf_name, conf_value, comment, &default_float_value);\
	if (ret != UB_CONF_SUCCESS && ret != UB_CONF_DEFAULT) {\
		exit(1); \
	} \
}while(0)


/**
 * @brief 一次只获取一个配置项的宏
 *
 */
#define UB_CONF_GETONESTR(path, filename, conf_name, n, conf_value) do {\
	if (ub_conf_getonenstr(path, filename, conf_name, n, conf_value) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETONEINT(path, filename, conf_name, conf_value) do {\
	if (ub_conf_getoneint(path, filename, conf_name, conf_value) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETONEUINT(path, filename, conf_name, conf_value) do {\
	if (ub_conf_getoneuint(path, filename, conf_name, conf_value) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETONEINT64(path, filename, conf_name, conf_value) do {\
	if (ub_conf_getoneint64(path, filename, conf_name, conf_value) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETONEUINT64(path, filename, conf_name, conf_value) do {\
	if (ub_conf_getoneuint64(path, filename, conf_name, conf_value) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0)

#define UB_CONF_GETONEFLOAT(path, filename, conf_name, conf_value) do {\
	if (ub_conf_getonefloat(path, filename, conf_name, conf_value) != UB_CONF_SUCCESS) {\
		exit(1); \
	} \
}while(0)


#define UB_CONF_GETONESVR(path, filename, product_name, module_name, comment) do {\
	if (ub_conf_getonesvr(path, filename, product_name, module_name, comment) != UB_CONF_SUCCESS) {\
		exit(1);\
	} \
}while(0)

#define UB_CONF_GETONEREQSVR(path, filename, product_name, module_name, comment) do {\
	if (ub_conf_getonereqsvr(path, filename, product_name, module_name, comment) != UB_CONF_SUCCESS) {\
		exit(1);\
	} \
}while(0)





#ifdef __cplusplus
}
#endif  //__cplusplus

#endif  //__UB_CONF_H__

/* vim: set ts=4 sw=4 tw=0 noet: */


