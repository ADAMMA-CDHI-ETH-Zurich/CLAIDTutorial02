#include "CLAID.hpp"
#include <string>

namespace HelloWorld
{
    // When creating a Module, inheriting from claid::Module is mandatory.
    class MyModule : public claid::Module
    {
        // Mandatory for a all Modules, this is required
        // to add de-/serialization support (e.g., from XML files).
        DECLARE_MODULE(MyModule)

        private:
            int myInteger;
            float myFloat;
            std::string myString;

            void initialize()
            {
                printf("MyInteger is %d\n", myInteger);
                printf("MyFloat is %f\n", myFloat);
                printf("MyString is \"%s\"\n", myString.c_str());
            }


        // Add reflection to public part of the class definition.
        public:

            Reflect(MyModule,
                reflectMember(myInteger);
                reflectMember(myFloat);
                reflectMember(myString);
            )
    };
}
// This will add the Module to the ClassFactory. 
// It allows instantiating this Module from an XML configuration.
REGISTER_MODULE(HelloWorld::MyModule)


#include "Utilities/ArgumentParser.hpp"
int main(int argc, char** argv) 
{
    ArgumentParser parser(argc, argv);

    std::string configPath = "";
    parser.add_argument<std::string>("path", configPath, "", "");

    if(configPath == "")
    {
        printf("Error, no path to XML configuration specified.\n"
        "Please use ./MyApplication path path/to/xml/file.\n"
        "E.g.: ./MyApplication path TutorialConfig.xml\n");
        exit(0);
    }

    // Loading Modules from an XML file.    
    CLAID_RUNTIME->loadFromXML(configPath);

    // Starting CLAID Runtime, which automatically will initialize all Modules.
    CLAID_RUNTIME->start();

    return 0;
}
