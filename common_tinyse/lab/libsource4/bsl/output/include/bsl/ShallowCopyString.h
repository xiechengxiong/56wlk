/***************************************************************************
 * 
 * 
 **************************************************************************/

/**
 * @file ShallowCopyString.h
 * @brief 
 *  
 **/

#ifndef  __SHALLOWCOPYSTRING_H_
#define  __SHALLOWCOPYSTRING_H_
#include <cstring>
#include <iostream>
#include "bsl/exception/bsl_exception.h"
#include "bsl/containers/string/bsl_string.h"

namespace bsl{

    class ShallowCopyString{
    public:
        typedef char            value_type;
        typedef size_t          size_type;
        typedef long            difference_type;
        typedef value_type &    reference;
        typedef const reference const_reference;
        typedef value_type *    pointer;
        typedef const pointer   const_pointer;
        typedef pointer         iterator;
        typedef const_pointer   const_iterator;
#if __GNUC__ <= 2
        typedef string_char_traits<value_type> traits_type;
#else
        typedef std::char_traits<value_type> traits_type;
#endif
        //ctors and dtors

        /**
         * @brief Ĭ�Ϲ��캯��
         *
         * Ĭ�Ϲ����ShallowCopyString��ʾ�մ���
         * @param [in] str   : const char*
         * @see 
         **/
        ShallowCopyString() 
            : _str(_S_EMPTY_CS), _length(0){}

        /**
         * @brief ��ʽ���캯��
         *
         * �ú�����C����ַ���ת��ΪShallowCopyString��
         *
         * �÷���ʱ�临�Ӷ�ΪO(1)�����ȱ�������ֵ����ֱ��size()������һ�α����ã�
         *
         * @param [in] str   : const char*
         * @see 
        **/
        ShallowCopyString( const char * str )  
            : _str(str), _length(npos) {
                if ( NULL == str ){
                    throw NullPointerException()<<BSL_EARG<<"str is NULL";
                }
            }

        /**
         * @brief ��C����ַ�����ָ���ĳ��ȹ���ShallowCopyString
         *
         * ע�⣺len������strlen(str)��ȣ�������Ϊδ���塣
         *
         * @param [in] str   : const char*
         * @param [in] len   : size_t
         * @see 
        **/
        ShallowCopyString( const char * str, size_t len ) 
            : _str(str), _length(len){
                if ( NULL == str ){
                    throw NullPointerException()<<BSL_EARG;
                }
                if ( str[len] != '\0' ){
                    //�����ĳ���ֵ����
                    throw bsl::BadArgumentException()<<BSL_EARG<<"wrong len:"<<len;
                }
            }

        /**
         * @brief ��ʹ������allocator���ɵ�bsl::basic_string����ShallowCopyString
         *
         * @param [in] bsl::basic_string<char   : const
         * @param [in] bsl_str   : allocator_t>&
         * @return  template<class allocator_t> 
         * @retval   
         * @see 
        **/
        template<class allocator_t>
        ShallowCopyString( const bsl::basic_string<char, allocator_t>& bsl_str )
            : _str(bsl_str.c_str()), _length(bsl_str.length()) {};

        /**
         * @brief ʹ��AutoBuffer����ShallowCopyString
         *
         * @param [in] buf   : const bsl::AutoBuffer&
         * @see 
        **/
        ShallowCopyString( const bsl::AutoBuffer& buf )
            : _str(buf.c_str()), _length(buf.size()){}

        /**
         * @brief ���ƹ��캯��
         *
         * @param [in] sstr   : const ShallowCopyString&
         * @see 
        **/
        ShallowCopyString( const ShallowCopyString& sstr ) 
            : _str(sstr._str), _length(sstr._length) {}

        /**
         * @brief ��������
         *
         * @see 
        **/
        ~ShallowCopyString() {
            //do nothing
        }

        void clear(){
            _str = _S_EMPTY_CS;
            _length = 0;
        }
        // getters
        /**
         * @brief ����C����ַ���
         *
         * @return  const char* 
         * @retval   
         * @see 
        **/
        const char * c_str() const  {
            return _str;
        }

        /**
         * @brief �����ַ�������
         *
         * ���ַ���ʹ��ShallowCopyString(const char *)���첢�ұ�������δ���ù���ʱ�临��Ϊ��O(strlen(this->c_str()))������ΪO(1)
         *
         * @return  size_t 
         * @retval   
         * @see 
        **/
        size_t size() const {
            if ( _length == npos ){
                const_cast<size_t&>(_length) = strlen(_str);
            }
            return _length;
        }

        /**
         * @brief ����size()
         *
         * @return  size_t 
         * @retval   
         * @see 
        **/
        size_t length() const {
            return size();
        }

        /**
         * @brief ����size()
         *
         * @return  size_t 
         * @retval   
         * @see 
        **/
        size_t capacity() const {
            return size();
        }
        
        /**
         * @brief ���ص�idx���ַ�
         *
         * ע�������������idx�ĺϷ���
         * @param [in] idx   : size_t
         * @return  char[] 
         * @retval   
         * @see 
        **/
        char operator []( size_t idx ) const {
            return _str[idx];
        }

        /**
         * @brief ���ص�idx���ַ�
         *
         * ���������idx�Ϸ��ԣ���idx>=this->size()���׳�bsl::OutOfBoundException
         * @param [in] idx   : size_t
         * @return  char 
         * @retval   
         * @see 
        **/
        char at( size_t idx ) const {
            if ( idx < this->size() ){
                return _str[idx];
            }
            throw bsl::OutOfBoundException()<<BSL_EARG<<"idx:"<<idx<<" size():"<<size();
        }
            
        /**
         * @brief ���Ƹ�ֵ
         *
         * ǳ���ƣ�ʱ�临�Ӷ�ΪO(1)
         * @param [in] sstr   : const ShallowCopyString&
         * @return  ShallowCopyString&  operator 
         * @retval   
         * @see 
        **/
        ShallowCopyString& operator = ( const ShallowCopyString& sstr ){
            _str        = sstr._str;
            _length     = sstr._length;
            return *this;
        }

        ShallowCopyString& operator = ( const AutoBuffer& buf ){
            _str        = buf.c_str();
            _length     = buf.size();
            return *this;
        }

        ShallowCopyString& operator = ( const bsl::string& str ){
            _str        = str.c_str();
            _length     = str.size();
            return *this;
        }

        ShallowCopyString& operator = ( const char *cstr ){
            if ( cstr == NULL ){
                throw bsl::NullPointerException()<<BSL_EARG<<"cstr is NULL";
            }
            if ( cstr != _str ){
                _str        = cstr;
                _length     = npos;
            }
            return *this;
        }

        /**
         * @brief �ֵ���Ƚ�
         *
         * �����ַ����ֵ���С�ڡ����ڡ�����other���򷵻�ֵ<0��=0��>0
         * �����ַ�������ĸ����ͬ�����ַ�����ַ��ͬ���ú���ʱ�临�Ӷ�ΪO(1)
         * 
         *
         * @param [in] other   : const ShallowCopyString&
         * @return  int 
         * @retval   
         * @see 
        **/
        int compare( const ShallowCopyString& other ) const {
            if ( _str[0] != other._str[0] ){
                return traits_type::lt(_str[0], other._str[0]) ? -1 : 1;
            }
            if ( _str == other._str ){
                return 0;   //����ShallowCopyString��˵�����п��ܵġ�
            }
            size_t min_size = std::min( size() , other.size() );
            int ret = memcmp( _str, other._str, min_size );
            if ( ret == 0 ){
                return _length - other._length;
            }else{
                return ret;
            }
        }

        //comparers
        //��Ϊconst char *ת��ΪShallowCopyString��O(1)�ģ�ShallowCopyString��һ�������C�ַ����Ƚ�Ҳ��ƽ��O(1)�ģ�Ԥ�жϵ�һ�ֽڣ������Բ�ר�Ŷ�C�ַ������ȽϺ����ˡ�
        friend inline bool operator == (const ShallowCopyString& sstr1, const ShallowCopyString& sstr2){
            return sstr1.compare( sstr2 ) == 0;
        }

        friend inline bool operator != (const ShallowCopyString& sstr1, const ShallowCopyString& sstr2){
            return sstr1.compare( sstr2 ) != 0;
        }

        friend inline bool operator < (const ShallowCopyString& sstr1, const ShallowCopyString& sstr2){
            return sstr1.compare( sstr2 ) < 0;
        }

        friend inline bool operator > (const ShallowCopyString& sstr1, const ShallowCopyString& sstr2){
            return sstr1.compare( sstr2 ) > 0;
        }

        friend inline bool operator <= (const ShallowCopyString& sstr1, const ShallowCopyString& sstr2){
            return sstr1.compare( sstr2 ) <= 0;
        }

        friend inline bool operator >= (const ShallowCopyString& sstr1, const ShallowCopyString& sstr2){
            return sstr1.compare( sstr2 ) >= 0;
        }

        /**
         * @brief ����������
         *
         * @param [in] os   : std::ostream&
         * @param [in] sstr   : const ShallowCopyString&
         * @return  friend inline std::ostream&  operator 
         * @retval   
         * @see 
        **/
        friend inline std::ostream& operator << ( std::ostream& os, const ShallowCopyString& sstr ){
            return os << sstr._str ;
        }
        
        static const size_t npos = static_cast<size_t>(-1);

    private:
        const char *    _str;
        size_t          _length;

        static const char _S_EMPTY_CS[];
    };
}   // namespace bsl

/**
 * @brief ����bsl::ShallowCopyString׷�ӵ�bsl::AutoBuffer�������
 *
 * @param [in] buf   : bsl::AutoBuffer&
 * @param [in] str   : bsl::ShallowCopyString&
 * @return  bsl::AutoBuffer&  operator 
 * @retval   
 * @see 
**/
inline bsl::AutoBuffer& operator <<( bsl::AutoBuffer& buf, bsl::ShallowCopyString& str ){
    return buf.push(str.c_str(), str.length());
}

#if __GNUC__ >=3
namespace __gnu_cxx{
#else
namespace std{
#endif
    /**
    * @brief ���__gnu_cxx::hash��д��hasher
    *  
    *  ʹ����const char*��ͬ��hash�㷨��
    */
    template<>
    struct hash<bsl::ShallowCopyString>{
        size_t operator()(const bsl::ShallowCopyString& str ) const {
            return __stl_hash_string(str.c_str());
        }
    };
}   // namespace __gnu_cxx/std

namespace bsl{
    /**
    * @brief ���bsl::xhash��д��hasher
    *  
    *  ʹ����const char*��ͬ��hash�㷨��
    */
    template<>
    struct xhash<bsl::ShallowCopyString>{
        size_t operator()(const bsl::ShallowCopyString& str ) const {
            return __bsl_hash_string(str.c_str());
        }
    };
}   // namespace bsl

#endif  //__SHALLOWCOPYSTRING_H_
/* vim: set ts=4 sw=4 sts=4 tw=100 */