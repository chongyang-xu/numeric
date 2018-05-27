#ifndef DEV_UTIL_TYPE_UTIL_H
#define DEV_UTIL_TYPE_UTIL_H

// Disable the copy and assignment operator for a class.
#define DENY_COPY_ASSIGN(Type)			\
   Type(const Type&)=delete;			\
   const Type& operator=(const Type&)=delete	\

//many other deny for complier default method
//...
//...
//read code to learn c++
//https://github.com/google/leveldb.git

#endif
