#include "Examples.h"

//Define the meta for Vector2 class
RDEFINE_CLASS(Vector2,object)
RDEFINE_PUBLIC_MEMBER(Vector2,x,Float32)
RDEFINE_PUBLIC_MEMBER(Vector2,y,Float32)

//Define the meta for Colors class (enum)
RDEFINE_ENUM(Colors)
RENUM_CPP(Colors,Values,Values::Purple +1)
{
	"Red",
	"Green",
	"Blue",
	"Purple"
};

//Define the meta for Shape class and its member methods.
RDEFINE_CLASS(Shape,Object)
RDEFINE_PROTECTED_MEMBER(Shape, m_VertexData, Array<Vector2>)

RDEFINE_PUBLIC_FUNCTION(Shape,SetVertexData,void, const Array<Vector2>&)
void Shape::SetVertexData(const Array<Vector2>& aVertexData)
{
	Array<Vector2>::Copy(aVertexData, m_VertexData);
}

RDEFINE_PUBLIC_FUNCTION(Shape,GetVertexData, Array<Vector2>)
Array<Vector2> Shape::GetVertexData()
{
	Array<Vector2> data;
	Array<Vector2>::Copy(m_VertexData, data);
	return data;
}

RDEFINE_PUBLIC_FUNCTION(Shape,GetVertexCount,int)
int Shape::GetVertexCount()
{
	return -1;
}

RDEFINE_PUBLIC_FUNCTION(Shape, OnRender, void, Vector2, Vector2, Vector2, SInt32, Float32)
void Shape::OnRender(Vector2 position, Vector2 scale, Vector2 rotation, SInt32 pass, Float32 z)
{

}

//Define the meta for IUpdater class and its member methods.
RDEFINE_INTERFACE(IUpdater)
RDEFINE_PUBLIC_FUNCTION(IUpdater, OnUpdate, void, Float32)
void IUpdater::OnUpdate(Float32 deltaTime)
{

}

//Define the meta for Triangle class and its member methods.
RDEFINE_CLASS(Triangle, Shape)
RDEFINE_PUBLIC_FUNCTION(Triangle, GetVertexCount, int)
int Triangle::GetVertexCount()
{
	return 3;
}
RDEFINE_PUBLIC_FUNCTION(Triangle, OnRender, void, Vector2, Vector2, Vector2, SInt32, Float32)
void Triangle::OnRender(Vector2 position, Vector2 scale, Vector2 rotation, SInt32 pass, Float32 z)
{
	//TODO: Draw this triangle with our m_VertexData at the position with the given scale and rotation.
	//Maybe use the pass to determine what special operations to enable.
	printf("Rendering a triangle at position %f %f\n", position.x, position.y);
}

//Define the meta for Square class and its member methods.
RDEFINE_CLASS(Square, Shape)
RDEFINE_PUBLIC_FUNCTION(Square, GetVertexCount, int)
int Square::GetVertexCount()
{
	return 4;
}
RDEFINE_PUBLIC_FUNCTION(Square, OnRender, void, Vector2, Vector2, Vector2, SInt32, Float32)
void Square::OnRender(Vector2 position, Vector2 rotation, Vector2 scale, SInt32 pass, Float32 z)
{
	//TODO: Draw this triangle with our m_VertexData at the position with the given scale and rotaiton.
	//Maybe use the pass to determine what special operations to enable.
	printf("Rendering a square at position %f %f\n", position.x, position.y);
}


//Define the meta for Super Triangle and its member methods

RDEFINE_CLASS(SuperTriangle, Triangle)
RDEFINE_ATTRIBUTE_INTERFACE(SuperTriangle, IUpdater)

RDEFINE_PRIVATE_MEMBER(SuperTriangle, m_Red,Float32)
RDEFINE_PRIVATE_MEMBER(SuperTriangle, m_Green, Float32)
RDEFINE_PRIVATE_MEMBER(SuperTriangle, m_Blue, Float32)

RDEFINE_PUBLIC_FUNCTION(SuperTriangle,OnRender, void, Vector2, Vector2, Vector2, SInt32, Float32)
void SuperTriangle::OnRender(Vector2 position, Vector2 rotation, Vector2 scale, SInt32 pass, Float32 z)
{

}
RDEFINE_PUBLIC_FUNCTION(SuperTriangle, OnUpdate, void, Float32)
void SuperTriangle::OnUpdate(Float32 deltaTime)
{

}

RDEFINE_PUBLIC_FUNCTION(SuperTriangle, SetRed, void, Float32)
RDEFINE_PUBLIC_FUNCTION(SuperTriangle, SetGreen, void, Float32)
RDEFINE_PUBLIC_FUNCTION(SuperTriangle, SetBlue, void, Float32)
RDEFINE_PUBLIC_FUNCTION(SuperTriangle, GetRed, Float32)
RDEFINE_PUBLIC_FUNCTION(SuperTriangle, GetGreen, Float32)
RDEFINE_PUBLIC_FUNCTION(SuperTriangle, GetBlue, Float32)

/** This method prints all types.*/
void PrintAllTypes();
/** This method creates an object based on type information*/
object * CreateType(Type & type);
/** This method destroys an object based on the type information from object*/
object * DestroyType(object * obj);
/** This method creates all the objects for this example using reflection.*/
void AddObjects(std::vector<object*> & objects);
/** This destroys all objects that were created in the vector using reflection.*/
void RemoveObjects(std::vector<object*> & objects);
/** This method checks if certain classes are derived from any of all types. */
void DerivedClassCheck(std::vector<object*> & objects);
/** This method demonstrates invoking a reflected method of an object.*/
void MethodExample(std::vector<object*> & objects);

void MemberExample(std::vector<object*> & objects);

void EnumExample(std::vector<object*> & objects);

void CheckEnum(const std::string & aString);
Colors StringToColor(const std::string & aString);

/** This method will attempt to get a function by name from each of the objects and invoke it.*/
template<typename CLASS, typename RETURN, typename ... ARGS>
void MethodCheck(const std::string & aFunctionName, std::vector<object*> & objects, ARGS...args)
{
	using namespace Gem::Reflection;
	for (int i = 0; i < objects.size(); i++)
	{
		//Get the type at runtime
		Type type = objects[i]->GetType();
		//Get the method at runtime.
		Member* method = type.GetMethodInfo(aFunctionName);

		//Attempt to cast the method to the proper methodinfo
		MethodInfo<CLASS, RETURN, ARGS...>* methodInfo = dynamic_cast<MethodInfo<CLASS, RETURN, ARGS...>*>(method);
		
		if (methodInfo != nullptr)
		{
			printf("%s is a method from class %s\n", aFunctionName.c_str(), type.GetName().c_str());
			//Invoke the method with the right arguments.
			methodInfo->GetMethod().Invoke((CLASS*)objects[i], args...);
			//methodInfo->GetMethod()->Invoke(objects[i], args...);
		}
		else
		{
			if (method == nullptr)
			{
				printf("%s is not a method from class %s\n", aFunctionName.c_str(), type.GetName().c_str());
			}
			else
			{
				//printf("%s is a method from class %s but the return type or arguments are invalid.\n", aFunctionName.c_str(), type.GetName().c_str());
			}
		}
	}
}

int Example()
{
	//Use the reflection namespace to get access to reflection types.
	using namespace Gem::Reflection;

	//Initialize and compile the Runtime. This will search for all type information
	//and build type objects.
	Runtime::Compile(nullptr);

	//Print all the types and their methods and members to the console.
	printf("\n===============================\n");
	printf("====   Printing all types  ====\n");
	printf("===============================\n\n");
	PrintAllTypes();
	
	std::vector<object*> objects;
	
	//Add a handful of objects into the vector using malloc and reflection.
	//This invokes the constructor.
	AddObjects(objects);

	printf("\n===============================\n");
	printf("====  Derived Class Check  ====\n");
	printf("===============================\n\n");
	DerivedClassCheck(objects);

	printf("\n===============================\n");
	printf("====     Method Example    ====\n");
	printf("===============================\n\n");
	MethodExample(objects);

	printf("\n===============================\n");
	printf("====     Member Example    ====\n");
	printf("===============================\n\n");
	MemberExample(objects);

	printf("\n===============================\n");
	printf("====     Enum Example    ====\n");
	printf("===============================\n\n");
	EnumExample(objects);
	
	//Remove all of the added objects using free and reflection.
	//This invokes the destructor.
	RemoveObjects(objects);


	//Terminate the runtime and free resources allocated.
	Runtime::Terminate();
	system("pause");
	

	return 0;
}

void PrintAllTypes()
{
	//Get all the types during the runtime and print out its type and its methods and the class who owns the original method.
	using namespace Gem::Reflection;
	Array<Type> types = Runtime::GetAllTypes();
	for (int i = 0; i < types.GetCount(); i++)
	{
		Type & type = types[i];
		Array<Member*> methods = type.GetMethods();
		for (int j = 0; j < methods.GetCount(); j++)
		{
			printf("%s | %s::%s\n", type.GetName().c_str(), methods[j]->GetClassName(), methods[j]->GetMemberName());
		}
		Array<MemberInfo> members = type.GetMembers();
		for (int j = 0; j < members.GetCount(); j++)
		{
			printf("%s | %s::%s\n", type.GetName().c_str(), members[j].GetClassName(), members[j].GetMemberName());
		}
	}
}

object * CreateType(Type & type)
{
	//If a objects type size is 0 it cannot be created.
	if (type.GetSize() == 0)
	{
		return nullptr;
	}
	//Allocate memory using malloc with the size of the type.
	object* obj = (object*)malloc(type.GetSize());
	//Invoke the default constructor with obj.
	return (object*)type.GetConstructor().Invoke(obj);
}
object * DestroyType(object * obj)
{
	if (obj == nullptr)
	{
		return nullptr;
	}
	//Get the type from the object to get runtime information of the object.
	Type type = obj->GetType();
	//Get the destructor and invoke it
	type.GetDestructor().Invoke(obj);
	//Free the memory
	free(obj);
	return nullptr;
}

void AddObjects(std::vector<object*> & objects)
{
	using namespace Gem::Reflection;
	//Use this object for getting type information.
	object * exampleTypeObject = new SuperTriangle();

	//To get type information there are 3 ways.
	//Using a string 
	Type triangleType = Runtime::TypeOf("Triangle");
	//Using a template, as long as the type is defined with TYPE_DEFINE(TYPE) macro.
	Type squareType = Runtime::TypeOf<Square>();
	//Using an existing reference of an object.
	Type superTriangleType = exampleTypeObject->GetType();
	delete exampleTypeObject;
	


	objects.push_back(CreateType(triangleType));
	objects.push_back(CreateType(squareType));
	objects.push_back(CreateType(superTriangleType));


}

void RemoveObjects(std::vector<object*> & objects)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i] = DestroyType(objects[i]);
	}
	objects.clear();
}

void DerivedClassCheck(std::vector<object*> & objects)
{
	using namespace Gem::Reflection;

	//Get all the types compiled in the Runtime class
	Array<Type> allTypes = Runtime::GetAllTypes();

	//Go through each object in objects vector and check against all types to see if any are 
	//the base class of the object.
	for (int j = 0; j < objects.size(); j++)
	{
		Type type = objects[j]->GetType();
		for (int i = 0; i < allTypes.GetCount(); i++)
		{
			if (Runtime::IsBaseOf(type, allTypes[i]))
			{
				printf("%s is derived from %s\n", type.GetName().c_str(), allTypes[i].GetName().c_str());
			}
			else
			{
				printf("%s is not derived from %s\n", type.GetName().c_str(), allTypes[i].GetName().c_str());
			}
		}
	}

}

void MethodExample(std::vector<object*> & objects)
{
	using namespace Gem::Reflection;

	//Invoke some methods using reflection.
	//There a problem with doing this however. 
	//A method for triangle, square, and super triangle cannot be downcasted to shape.
	//However it's possible to get the method from the base class (Shape) and use its on all
	//derived classes which can be seen below.

	//This method fails to cast Triangle, Square and SuperTriangle to MethodInfo<Shape,int>
	MethodCheck<Shape, int>("GetVertexCount", objects);
	//This method fails to cast Square to MethodInfo<Shape,int> but works for Triangle and SuperTriangle
	MethodCheck<Triangle, int>("GetVertexCount", objects);
	//This method fails to cast just as the first MethodCheck call.
	MethodCheck<Shape, void, Vector2, Vector2, Vector2, SInt32, Float32>(
		"OnRender",
		objects,
		{ 0.0f, 0.0f }, //position
		{ 0.0f, 0.0f }, //scale
		{ 0.0f, 0.0f }, //rotation
		0,				//pass
		0.0f);			//z

	//Shape
	{
		//If we get the method GetVertexCount from the base class Shape we can use it
		//on each of the classes and they will invoke the correct method of the class.
		Member* method = Runtime::TypeOf("Shape").GetMethodInfo("GetVertexCount");

		MethodInfo<Shape, int>* methodShape = dynamic_cast<MethodInfo<Shape, int>*>(method);
		MethodInfo<Triangle, int>* methodTriangle = dynamic_cast<MethodInfo<Triangle, int>*>(method);
		MethodInfo<Square, int>* methodSquare = dynamic_cast<MethodInfo<Square, int>*>(method);
		MethodInfo<SuperTriangle, int>* methodSuperTriangle = dynamic_cast<MethodInfo<SuperTriangle, int>*>(method);

		for (int i = 0; i < objects.size(); i++)
		{
			int vertexCount = methodShape->GetMethod().Invoke((Shape*)objects[i]);
			printf("Shape %s has %d vertices\n",
				objects[i]->GetType().GetName().c_str(),
				vertexCount);
		}
	}


	//Triangle - Demonstrating the casting fail cases.
	{
		Member* method = objects[0]->GetType().GetMethodInfo("GetVertexCount");

		MethodInfo<Shape, int>* methodShape = dynamic_cast<MethodInfo<Shape, int>*>(method);
		MethodInfo<Triangle, int>* methodTriangle = dynamic_cast<MethodInfo<Triangle, int>*>(method);
		MethodInfo<Square, int>* methodSquare = dynamic_cast<MethodInfo<Square, int>*>(method);
		MethodInfo<SuperTriangle, int>* methodSuperTriangle = dynamic_cast<MethodInfo<SuperTriangle, int>*>(method);
	}
	//Square - Demonstrating the casting fail cases.
	{
		Member* method = objects[1]->GetType().GetMethodInfo("GetVertexCount");

		MethodInfo<Shape, int>* methodShape = dynamic_cast<MethodInfo<Shape, int>*>(method);
		MethodInfo<Triangle, int>* methodTriangle = dynamic_cast<MethodInfo<Triangle, int>*>(method);
		MethodInfo<Square, int>* methodSquare = dynamic_cast<MethodInfo<Square, int>*>(method);
		MethodInfo<SuperTriangle, int>* methodSuperTriangle = dynamic_cast<MethodInfo<SuperTriangle, int>*>(method);

	}
	//SuperTriangle - Demonstrating the casting fail cases.
	{
		Member* method = objects[2]->GetType().GetMethodInfo("GetVertexCount");


		MethodInfo<Shape, int>* methodShape = dynamic_cast<MethodInfo<Shape, int>*>(method);
		MethodInfo<Triangle, int>* methodTriangle = dynamic_cast<MethodInfo<Triangle, int>*>(method);
		MethodInfo<Square, int>* methodSquare = dynamic_cast<MethodInfo<Square, int>*>(method);
		MethodInfo<SuperTriangle, int>* methodSuperTriangle = dynamic_cast<MethodInfo<SuperTriangle, int>*>(method);

	}
}

void MemberExample(std::vector<object*> & objects)
{
	using namespace Gem::Reflection;

	float x = 0.0f;
	float y = 0.0f;

	for (std::vector<object*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		Type type = (*it)->GetType();
		MemberInfo info = type.GetMember("m_VertexData");


		//This will throw a exception std::__non_rtti_object most likely because the m_VertexData
		//member is not an actual pointer.
		//Array<Vector2> * errorCase = dynamic_cast<Array<Vector2>*>(info.GetOffsetPointer(*it));

		//Alternatively reflection can be used to check the type and then use a CStyle cast.
		//This should work as long as the write names were written in the macro.
		if (strcmp(info.GetMemberTypename(), "Array<Vector2>") == 0)
		{
			Array<Vector2> * vertexData = (Array<Vector2>*)(info.GetOffsetPointer(*it));

			if (vertexData != nullptr)
			{
				vertexData->Allocate(3);
				(*vertexData)[0] = Vector2(x, y);
				x += 0.5f;
				y += 0.5f;
				(*vertexData)[1] = Vector2(x, y);
				x += 0.5f;
				y += 0.5f;
				(*vertexData)[2] = Vector2(x, y);
				x += 0.5f;
				y += 0.5f;
			}
		}

		
	}

	//Print out the vertex data of the objects.
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		Shape * shape = dynamic_cast<Shape*>(objects[i]);
		if (shape != nullptr)
		{
			Array<Vector2> & vertexData = shape->GetVertexData();
			Type type = (objects[i])->GetType();
			for (int i = 0; i < vertexData.GetCount(); i++)
			{
				printf("%s m_VertexData[%d] = %f, %f\n", type.GetName().c_str(), i, vertexData[i].x, vertexData[i].y);
			}
		}
		
	}

}

void CheckEnum(const std::string & aString)
{
	//Convert a string to a color. (This is slow but possible with reflection.)
	Colors color = StringToColor(aString);
	if (Enum::IsValid(&color))
	{
		printf("%s is a valid color name with the id %d.\n", aString.c_str(), (SInt32)color);
	}
	else
	{
		printf("%s is a an invalid color name.\n", aString.c_str());
	}
}

void EnumExample(std::vector<object*> & objects)
{
	//Create a color enum
	Colors color = Colors::Red;

	//Colors have an implicit operator for ints , SInt32)
	SInt32 colorID = color;
	//Colors also have implicit operator for const char * types.
	CString colorName = color;
	printf("Color ID = %d\nColor Name = %s\n", colorID, colorName);

	//Checks to see if there is an enum named "Red"
	CheckEnum("Red");
	//Checks to see if there is an enum named "Green"
	CheckEnum("Green");
	//Checks to see if there is an enum named "Blue"
	CheckEnum("Blue");
	//Checks to see if there is an enum named "Yellow"
	CheckEnum("Yellow");
	
}

Colors StringToColor(const std::string & aString)
{
	//Get all the names from colors enum.
	Array<std::string> names = Enum::GetNames(&Colors());
	for (int i = 0; i < names.GetCount(); i++)
	{
		if (names[i] == aString)
		{
			return i; //Implicit Converstion.
		}
	}
	return Enum::InvalidEnum(); //Default Value Invalid Enum -1
}