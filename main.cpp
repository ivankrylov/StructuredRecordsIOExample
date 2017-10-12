#include <iostream>
#include <string>
#include <map>

namespace StructuredRecords {

    enum class Record_Types {
        Unknown_Type,
        Car_Type,
        Fruit_Type,
        Unrecognized_Type
    };

    namespace Record_Type_Names {
        const std::string Unknown_Str = "Unknown";
        const std::string Car_Str = "Car";
        const std::string Fruit_Str = "Fruit";
        const std::string Unrecognized_Str = "Unrecognized";
    };

    class Base_Record_Class {
    public:

        template<class T>
        static void RegisterItemTypes(Record_Types record_type, std::string record_name) {
            _factories_from_types[record_type] = &itemFactory<T>;
            _factories_from_names[record_name] = &itemFactory<T>;

            T* temp_element = (T*) (itemFactory<T>());
            temp_element->_record_type = record_type;
            temp_element->_record_name = record_name;
            delete temp_element;
        }

        static Base_Record_Class* getItemFactory(Record_Types type) {
            std::map<Record_Types, FactoryFunctor>::iterator C = _factories_from_types.find(type);
            if (C == _factories_from_types.end())
                return nullptr;
            return C->second();
        }

        static Record_Types _record_type;
        static std::string _record_name;

        friend std::ostream& operator<< (std::ostream &stream, const Base_Record_Class &item) {
            stream << "Type of item: " << (int) item._record_type;
            return stream;
        }



        typedef Base_Record_Class* (*FactoryFunctor)();
    private:
        template<class T>
        static Base_Record_Class* itemFactory() {
            Base_Record_Class* result = new T();
            return result;
        }

    private:

        static std::map <Record_Types, FactoryFunctor> _factories_from_types;
        static std::map <std::string, FactoryFunctor> _factories_from_names;
    };

    class Car_Record_Class : public Base_Record_Class {
        std::string _make;
        int _year;

    public:
        static Record_Types _record_type;
        static std::string _record_name;

        Car_Record_Class* set_make(std::string make) {
            _make = make;
            return this;
        }
        Car_Record_Class* set_year(int year) {
            _year = year;
            return this;
        }
        friend std::ostream& operator<< (std::ostream &stream, const Car_Record_Class *item) {
            stream << "Type of item: " << (int) item->_record_type << " make:" << item->_make << " year:" << item->_year;
            return stream;
        }
    };

    class Fruit_Record_Class : public Base_Record_Class {
    private:
        std::string _name, _color;
    public:
        static Record_Types _record_type;
        static std::string _record_name;

        Fruit_Record_Class* set_name(std::string name) {
            _name = name;
            return this;
        }
        Fruit_Record_Class* set_color(std::string color) {
            _color = color;
            return this;
        }
        friend std::ostream& operator<< (std::ostream &stream, Fruit_Record_Class *item) {
            stream << "Type of item: " << (int) item->_record_type << " name:" << item->_name << " color:" << item->_color;
            return stream;
        }
    };
}

using namespace StructuredRecords;

// Materialization of class's statics to make the linekr happy
std::map <Record_Types, Base_Record_Class::FactoryFunctor> Base_Record_Class::_factories_from_types;
std::map <std::string, Base_Record_Class::FactoryFunctor> Base_Record_Class::_factories_from_names;
Record_Types Base_Record_Class::_record_type;
Record_Types Car_Record_Class::_record_type;
Record_Types Fruit_Record_Class::_record_type;
std::string Base_Record_Class::_record_name;
std::string Car_Record_Class::_record_name;
std::string Fruit_Record_Class::_record_name;

int main() {

    Base_Record_Class baseClass;

    std::cout << "Hello, World!" << std::endl;

    baseClass.RegisterItemTypes<Car_Record_Class>(Record_Types::Car_Type, Record_Type_Names::Car_Str);
    baseClass.RegisterItemTypes<Fruit_Record_Class>(Record_Types::Fruit_Type, Record_Type_Names::Fruit_Str);

    Car_Record_Class* car1 = ((Car_Record_Class*)(baseClass.getItemFactory(Record_Types::Car_Type)))->set_make("BMW")->set_year(2017);
    Car_Record_Class* car2 = ((Car_Record_Class*)(baseClass.getItemFactory(Record_Types::Car_Type)))->set_make("Mercedes")->set_year(2016);

    Fruit_Record_Class* fruit1 = ((Fruit_Record_Class*)(baseClass.getItemFactory(Record_Types::Fruit_Type)))->set_name("banana")->set_color("yellow");
    Fruit_Record_Class* fruit2 = ((Fruit_Record_Class*)(baseClass.getItemFactory(Record_Types::Fruit_Type)))->set_name("apple")->set_color("green");

    std::cout << car1 << std::endl;
    std::cout << car2 << std::endl;
    std::cout << fruit1 << std::endl;
    std::cout << fruit2 << std::endl;

    return 0;
}