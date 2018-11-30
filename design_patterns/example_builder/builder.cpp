Builder (Joshua Blosh)
The purpose of the builder design pattern proposed by Joshua Bloch is to simplify the instantiation of objects with many constructor parameters or many optional parameters. Note: it should not be confused with the GOF (Gang of Four) builder pattern.

Example:

File: builder.cpp
// Joshua Bloch's Builder Pattern for simplifying the instantiation
// of objects with many constructor parameters. It is not the
// GOF (Gang of Four) builder pattern. 
#include <iostream>
#include <string>

// Function meta object 
class UserData{
public:
        using ulong = unsigned long;
private:
        ulong          _userID = 0;
        std::string    _name;
        std::string    _lastName;
        std::string    _email;
        UserData() = default;
public:
        // Explicit is better than implicit 
        ~UserData() = default;
	
        auto show() -> void
        {
            std::cout << "\nUser{"
                      << "\n" << "  id        = " << _userID
                      << "\n" << "  name      = " << _name
                      << "\n" << "  last name = " << _lastName
                      << "\n" << "  email     = " << _email
                      << "\n" << "}"
                      << "\n";
        }
	
        // Allow builder class access UserData's private data
        friend class UserBuilder;
}; //--- EoF class UserData --- //

class UserBuilder{
private:
        //class UserData;
        UserData _data{};
public:
        UserBuilder(){
                // _data = UserData();
        }		
        auto setID(ulong userID ) -> UserBuilder& {
           _data._userID = userID;
           return *this;
        }
        auto setName(const std::string& name) -> UserBuilder& {
            _data._name = name;
            return *this;
        }
        auto setLastName(const std::string& name) -> UserBuilder& {
            _data._lastName = name;
            return *this;
        }
        auto setEmail(const std::string& email) -> UserBuilder& {
           _data._email = email;
           return *this;
        }
        auto build() -> UserData {
           return this->_data;
        }
}; //--- EoF class UserData::builder --- //

int main(){
    auto user0 =
            UserBuilder()
            .setID(2065)
            .setName("John")
            .setLastName("Von Neumman")
            .setEmail("nx098774a@sknmap.co")
            .build();
    auto user1 =
            UserBuilder()
            .setID(1065)
            .setName("Enrico")
            .setLastName("Fermi")
            .setEmail("dummyEmail@service1.co.uk")
            .build();
    auto user2 =
            UserBuilder()
            .setID(2001)
            .setName("Stanislaw")
            .setLastName("Ulam")
            .setEmail("wsx752@couk.com.sk")
            .build();
    user0.show();
    user1.show();		
    user2.show();
    return EXIT_SUCCESS;
}

