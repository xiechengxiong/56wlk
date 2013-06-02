/***************************************************************************
 * 
 * 
 **************************************************************************/



/**
 * @file String.h
 * @brief 
 *  
 **/
#ifndef  __BSL_VAR_STRING_H__
#define  __BSL_VAR_STRING_H__
#include "bsl/var/IVar.h"
#include "bsl/var/Ref.h"
#include "bsl/check_cast.h"
namespace bsl{
namespace var{
    class String: public IVar{
    public:
        typedef IVar::string_type   string_type;
        typedef IVar::field_type    field_type;

    public:
        //special methods
        String( ): _value() {}

        String( const String& other )
            :IVar(other), _value(other._value) { }

        String( const char * cstr )
            : _value(cstr) { }

        String( const char *cstr, size_t len )
            : _value(cstr, len) {}

        String( const string_type& value_ ): _value(value_){}

        String& operator = ( const String& other ){
            _value = other._value;
            return *this;
        }

        virtual ~String(){
            //pass
        }

        //methods for all
        virtual String& operator = ( IVar& var ){
            _value = var.to_string();
            return *this;
        }

        /**
         * @brief ���������Ϣ�������ڵ��ԣ���ͨ��verbose_level���Ƶݹ����
         *
         * @return  string_type 
         * @retval   
         * @see 
        **/
        virtual string_type dump(size_t /*verbose_level*/=0) const {
            return  string_type("[bsl::var::String]").append(_value);
        }

        /**
         * @brief ת��Ϊ�ַ���
         *
         * @return  string_type 
         * @retval   
         * @see 
        **/
        virtual string_type to_string() const {
            return _value;            
        }

        /**
         * @brief ��ȡ�����ַ���������var���Ͷ�֧�֣������ڵ���ʹ�ã������������жϣ�
         *
         * @return  string_type 
         * @retval   
         * @see 
        **/
        virtual string_type get_type() const {
            return "bsl::var::String";
        }

        /**
         * @brief ��ȡ�������루����var���Ͷ�֧�֣�
         *
         * @return  IVar::mask_type 
         * @retval   
         * @see 
        **/
        virtual IVar::mask_type get_mask() const {
            return IVar::IS_STRING;
        }

        /**
         * @brief ��������
         *
         * @return  void 
         * @retval   
         * @see 
         **/
        virtual void clear(){
            _value.clear();
        }

        /**
         * @brief ��¡����
         *
         * �ú���ֻ��¡������㣬����¡�ӽ�㣬���������ͣ���¡ָ��Ľ��
         *
         * @param [in] rp   : bsl::ResourcePool&
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& clone( bsl::ResourcePool& rp ) const {
            return rp.clone(*this);
        }

        //testers
        /**
         * @brief �ж��Ƿ����ַ�������
         *
         * @return  bool 
         * @retval   
         * @see 
        **/
        virtual bool is_string() const {
            return true;
        }

        //methods for value
        /**
         * @brief ת��Ϊ��������
         *
         * @return  bool 
         * @retval   
         * @see 
        **/
        virtual bool to_bool() const {
            return _value.c_str()[0] != '\0';
        }

        /**
         * @brief ת��Ϊ8λ�з����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  signed char 
         * @retval   
         * @see 
        **/
        virtual signed char to_int8() const {
            return check_cast<signed char>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ8λ�޷����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  unsigned char 
         * @retval   
         * @see 
        **/
        virtual unsigned char to_uint8() const {
            return check_cast<unsigned char>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ16λ�з����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  signed short 
         * @retval   
         * @see 
        **/
        virtual signed short to_int16() const {
            return check_cast<signed short>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ16λ�޷����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  unsigned short 
         * @retval   
         * @see 
        **/
        virtual unsigned short to_uint16() const {
            return check_cast<unsigned short>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ32λ�з����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  signed int 
         * @retval   
         * @see 
        **/
        virtual signed int to_int32() const {
            return check_cast<signed int>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ32λ�޷����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  unsigned int 
         * @retval   
         * @see 
        **/
        virtual unsigned int to_uint32() const {
            return check_cast<unsigned int>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ64λ�з����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  signed long long 
         * @retval   
         * @see 
        **/
        virtual signed long long to_int64() const {
            return check_cast<signed long long>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ64λ�޷����������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  unsigned long long 
         * @retval   
         * @see 
        **/
        virtual unsigned long long to_uint64() const {
            return check_cast<unsigned long long>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ�����ȸ��������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  float 
         * @retval   
         * @see 
        **/
        virtual float to_float() const {
            return check_cast<float>(_value.c_str());
        }

        /**
         * @brief ת��Ϊ˫���ȸ��������ͣ�����is_number()����������Ͷ�֧�֣�
         *
         * @return  double 
         * @retval   
         * @see 
        **/
        virtual double to_double() const {
            return check_cast<double>(_value.c_str());
        }

        virtual String& operator = ( bool b ){
            if ( b ){
                _value = "true";
            }else{
                _value = "false";
            }
            return *this;
        }

        /**
         * @brief ʹ��signed char���͸�ֵ
         *
         * @param [in] val   : signed char
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( signed char val ){
            _value.setf( "%hhd", val );
            return *this;
        }

        /**
         * @brief ʹ��unsigned char���͸�ֵ
         *
         * @param [in] val   : unsigned char
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( unsigned char val ){
            _value.setf( "%hhu", val );
            return *this;
        }
        /**
         * @brief ʹ��signed short���͸�ֵ
         *
         * @param [in] val   : signed short
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( signed short val ){
            _value.setf( "%hd", val );
            return *this;
        }
        /**
         * @brief ʹ��unsigned short���͸�ֵ
         *
         * @param [in] val   : unsigned short
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( unsigned short val ){
            _value.setf( "%hu", val );
            return *this;
        }
        /**
         * @brief ʹ��signed int���͸�ֵ
         *
         * @param [in] val   : signed int
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( signed int val ){
            _value.setf( "%d", val );
            return *this;
        }
        /**
         * @brief ʹ��unsigned int���͸�ֵ
         *
         * @param [in] val   : unsigned int
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( unsigned int val ){
            _value.setf( "%u", val );
            return *this;
        }
        /**
         * @brief ʹ��signed long long���͸�ֵ
         *
         * @param [in] val   : signed long long
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( signed long long val ){
            _value.setf( "%lld", val );
            return *this;
        }
        /**
         * @brief ʹ��unsigned long long���͸�ֵ
         *
         * @param [in] val   : unsigned long long
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( unsigned long long val ){
            _value.setf( "%llu", val );
            return *this;
        }

        /**
         * @brief ʹ��float���͸�ֵ
         *
         * @param [in] val   : float
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( float f ){
            _value.setf( "%f", f );
            return *this;
        }

        /**
         * @brief ʹ��double���͸�ֵ
         *
         * @param [in] val   : double
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( double d ){
            _value.setf( "%lf", d );
            return *this;
        }

        /**
         * @brief ʹ��const char *���͸�ֵ
         *
         * @param [in] val   : const char *
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( const char * cstr ){
            _value = cstr;
            return *this;
        }

        /**
         * @brief ʹ���ַ������͸�ֵ
         *
         * @param [in] val   : const string_type&
         * @return  String& 
         * @retval   
         * @see 
        **/
        virtual String& operator = ( const string_type& str ){
            _value = str;
            return *this;
        }

        //use default version for bool��raw
        using IVar::operator =;

        /**
         * @brief ����C����ַ�����ʾ
         *
         * ����is_string()����true��IVarʵ���඼����֧�ָ÷�����
         * ��ʵ���಻֧�ָò������׳�bsl::InvalidOperationException�쳣
         * @return  const char* 
         * @retval   
         * @see 
        **/
        virtual const char * c_str() const {
            return _value.c_str();
        }

        /**
         * @brief ����C����ַ�����ʾ�ĳ��ȣ�������ĩβ��'\0'
         *
         * ����is_string()����true��IVarʵ���඼����֧�ָ÷�����
         * ��ʵ���಻֧�ָò������׳�bsl::InvalidOperationException�쳣
         * @return  size_t 
         * @retval   
         * @see 
        **/
        virtual size_t c_str_len() const {
            return _value.size();
        }

    private:
        string_type _value;
    };

}}//namespace bsl::var

#endif  //__BSL_VAR_STRING_H__

/* vim: set ts=4 sw=4 sts=4 tw=100 */