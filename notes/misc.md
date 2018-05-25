google code spec //理解用意而不是照搬
# 五、代码规范

auto 只用于局部变量
sizof(Type)而不是sizeof(var_name)
C++11 nullptr C++01 NULL
vector<bool> 不是容器 why?
不使用宏条件编译，除非是防止头文件包含
<stdint.h>类型明确 int16_t int32_t
不使用流，除非是输出日志
不使用RTTI type_id,dynamic_cast
不使用异常 //因为谷歌已有的大部分代码没有使用
不使用变长数组和alloca
使用std::unique_ptr明确所有权传递
性能提升明显且对象不可变时才用 std::shared_ptr
C++ constexpr定义真常量


文件名:蛇形命名 o_o_o.cc
类型、模板参数类型： 驼峰命名
变量、成员变量、函数参数： 蛇形命名 class:a_class_var_, struct:a_struct_var 下划线
常量 k开头驼峰
命名空间 蛇形命名，避免冲突
函数命名 驼峰命名，getter,setter使用蛇形，和变量匹配
美枚举类型 和常量相同 驼峰命名 或者和宏一致
宏 大写加下划线
特例 命名实体和已有c/c++相似，采用以现有的方式
