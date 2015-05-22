#ifndef EXAMPLES_H
#define EXAMPLES_H

#include "../../Source/Engine.h"

//==========================================================================
// Gem Reflection
// This is a small framework used to add meta data to classes and enums. In this
// file and Examples.cpp there are examples on how to use it.
// 
// Examples include:
// • Creating a class and reflecting it
// • Reflecting members of a class
// • Reflecting methods of a class
// • Reflecting inherited interfaces of a class
// • Creating a enum and reflecting it to provide matching string / int data.
// • Allocating memory for objects and invoking the constructor with reflection
// • Deallocate memory of objects and invoking the destructor with reflection
// • Invoking methods on objects at runtime with reflection
// • Changing values of members at runtime with reflection.
// • Doing base class / derived class comparisons at runtime with reflection.
// • Getting type information at runtime
// • Use of enum classes
// 
//
// Unfortuneatly there is no support for template types and there must be some inheritance from 
// the class object.
//
// When adding meta data the macros come in two types. RDECLARE and RDEFINE
// RDECLARE is used in the header file to declare the data
// RDEFINE is used in the cpp file to define the data.
//
// All meta data is of type MetaObject<T> where T is class/interface/enum holding the meta data.
// Meta data is prefixed with the name HIDDEN_ and shouldnt be tempered with.
// 
// TYPE_DEFINE - This macro creates a template definition of the class which is required for the Reflection to work correctly.
// TYPE_DEFINE_NAMED - This macro is similar to TYPE_DEFINE however it allows the user to give a different name to the class.
//
// When adding member and method meta information use PUBLIC / PROTECTED / PRIVATE macros. 
// This automatically sets the access modifier to the corresponding macro used.
// 
// Class / Interface / Enum Macros
// • RDECLARE_CLASS, RDEFINE_CLASS
// • RDECLARE_INTERFACE, RDEFINE_INTERFACE
// • RDECLARE_ENUM, RDEFINE_ENUM
//
// Attribute Macros
// • RDECLARE_ATTRIBTE_INTERFACE, RDEFINE_ATTRIBUTE_INTERFACE
// • RDECLARE_ ... _MEMBER, RDEFINE_ ... _MEMBER (Replace ... with the appropriate access modifier)
// • RDECLARE_ ... _METHOD, RDEFINE_ ... _METHOD (Replace ... with the appropriate access modifier)
// 
// 
//==========================================================================

int Example();

using namespace Gem;



/**
* A class used to represent two floating point values.
*/
class Vector2 : public object
{
	//Declare the class meta data.
	RDECLARE_CLASS(Vector2)
public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(Float32 _x, Float32 _y) : x(_x), y(_y) {}
	//Declare a public member called x
	RDECLARE_PUBLIC_MEMBER(Vector2,x)
	Float32 x;
	//Declare a public member called y
	RDECLARE_PUBLIC_MEMBER(Vector2,y)
	Float32 y;
};

//Define a template meta for Vector2.
TYPE_DEFINE(Vector2)


/**
* A class used to represent enum values that are reflected.
*/
class Colors : public Enum
{
public:
	//Define the values in a public namespace.
	enum Values
	{
		Red,
		Green,
		Blue,
		Purple
	};
	//Use this macro to declare the meta data. 
	//This macro has a matching RDEFINE macro associated with it which is required in the cpp file.
	RDECLARE_ENUM(Colors)
	//Use this macro to add all the data for this class to be considered an enum.
	//This macro has a RENUM_CPP version which needs to be implemented in the CPP file with a string version of the enum.
	RENUM_H(Colors,Values, Values::Purple + 1)
};

TYPE_DEFINE(Colors)



/**
* The base class for all shapes. 
* All shapes have vertex data and can have different numbers 
* of vertices and different ways of rendering.
*/
class Shape : public Object
{
	RDECLARE_CLASS(Shape)
public:

	//Some Normal Methods
	RDECLARE_PUBLIC_FUNCTION(Shape, SetVertexData)
	void SetVertexData(const Array<Vector2> & aVertexData);
	RDECLARE_PUBLIC_FUNCTION(Shape, GetVertexData)
	Array<Vector2> GetVertexData();

	//Virtual Method
	RDECLARE_PUBLIC_FUNCTION(Shape, GetVertexCount)
	virtual int GetVertexCount();
	RDECLARE_PUBLIC_FUNCTION(Shape, OnRender)
	virtual void OnRender(Vector2 position, Vector2 scale, Vector2 rotation, SInt32 pass, Float32 z);
protected:
	RDECLARE_PROTECTED_MEMBER(Shape, m_VertexData)
	Array<Vector2> m_VertexData;
};

TYPE_DEFINE(Shape)


class IUpdater
{
	RDECLARE_INTERFACE(IUpdater)
public:
	RDECLARE_PUBLIC_FUNCTION(IUpdater, OnUpdate)
	virtual void OnUpdate(Float32 deltaTime);
};

TYPE_DEFINE(IUpdater)


class Triangle : public Shape
{
	RDECLARE_CLASS(Triangle)
public:
	RDECLARE_PUBLIC_FUNCTION(Triangle, GetVertexCount)
	int GetVertexCount() override;
	RDECLARE_PUBLIC_FUNCTION(Triangle, OnRender)
	virtual void OnRender(Vector2 position, Vector2 scale, Vector2 rotation, SInt32 pass, Float32 z) override;
};

TYPE_DEFINE(Triangle)

class Square : public Shape
{
	RDECLARE_CLASS(Square)
public:
	RDECLARE_PUBLIC_FUNCTION(Square, GetVertexCount)
	int GetVertexCount() override;
	RDECLARE_PUBLIC_FUNCTION(Square, OnRender)
	void OnRender(Vector2 position, Vector2 scale, Vector2 rotation, SInt32 pass, Float32 z) override;
};

TYPE_DEFINE(Square)

class SuperTriangle : public Triangle, public IUpdater
{
	RDECLARE_CLASS(SuperTriangle)
	RDECLARE_ATTRIBUTE_INTERFACE(SuperTriangle,IUpdater)
public:
	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, OnRender)
		void OnRender(Vector2 position, Vector2 scale, Vector2 rotation, SInt32 pass, Float32 z) override;
	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, OnUpdate)
		void OnUpdate(Float32 deltaTime) override;

	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, SetRed)
	inline void SetRed(Float32 aRed)
	{
		m_Red = aRed;
	}
	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, SetGreen)
	inline void SetGreen(Float32 aGreen)
	{
		m_Green = aGreen;
	}
	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, SetBlue)
	inline void SetBlue(Float32 aBlue)
	{
		m_Blue = aBlue;
	}

	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, GetRed)
	inline Float32 GetRed() const
	{
		return m_Red;
	}
	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, GetGreen)
	inline Float32 GetGreen() const
	{
		return m_Green;
	}
	RDECLARE_PUBLIC_FUNCTION(SuperTriangle, GetBlue)
	inline Float32 GetBlue() const
	{
		return m_Blue;
	}

private:
	RDECLARE_PRIVATE_MEMBER(SuperTriangle, m_Red)
	Float32 m_Red;
	RDECLARE_PRIVATE_MEMBER(SuperTriangle, m_Green)
	Float32 m_Green;
	RDECLARE_PRIVATE_MEMBER(SuperTriangle, m_Blue)
	Float32 m_Blue;
};


TYPE_DEFINE(SuperTriangle)


#endif