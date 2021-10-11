#include <utility>

//
// Created by lokt0 on 22.05.2021.
//

#ifndef LABA3_PERSON_H
#define LABA3_PERSON_H

#include <ctime>
#include <string>

using namespace std;

typedef struct PersonID{
    int series = 0;
    int number = 0;

    bool operator==(const PersonID &id) const {
        return series == id.series && number == id.number;
    }
} PersonID;

class Person{
private:
    PersonID id{};
    string firstName;
    string middleName;
    string lastName;
    time_t birthDate;
public:
    Person(const PersonID &id, string firstName, string middleName, string lastName, const time_t &birthDate) {
        this->id = id;
        this->firstName = std::move(firstName);
        this->middleName = std::move(middleName);
        this->lastName = std::move(lastName);
        this->birthDate = birthDate;
    };
    Person():Person({0, 0}, "", "", "", time(nullptr)){};

    Person(const Person &person):
    Person(person.id, person.firstName,
           person.middleName, person.lastName, person.birthDate) {};

    PersonID GetID() const {
        return id;
    }
    string GetFirstName(){
        return firstName;
    }
    string GetMiddleName(){
        return middleName;
    }
    string GetLastName(){
        return lastName;
    }
    [[nodiscard]] string GetFullName() const{
        return firstName + " " + middleName + " " + lastName;
    }
    [[nodiscard]] time_t GetBirthDate() const{
        return birthDate;
    }
    friend ostream& operator<<(ostream &out, const Person& person){
        out << "id: ";
        out << person.id.series;
        out << " ";
        out << person.id.number;
        out << ", full name: ";
        out << person.GetFullName();
        out << ", birth date: ";
        out << person.GetBirthDate();
        return out;
    }
    friend istream& operator>>(istream &in, Person& person){
        in >> person.id.number;
        in >> person.id.series;
        in >> person.firstName;
        in >> person.middleName;
        in >> person.lastName;
        in >> person.birthDate;
        return in;
    }
    bool operator<(const Person& person) const{
        return GetFullName() < person.GetFullName();
    }
    bool operator<=(const Person& person) const{
        return GetFullName() <= person.GetFullName();
    }
    bool operator>(const Person& person) const{
        return GetFullName() > person.GetFullName();
    }
    bool operator>=(const Person& person) const{
        return GetFullName() >= person.GetFullName();
    }
    bool operator==(const Person& person) const{
        return GetFullName() == person.GetFullName() && GetID() == person.GetID() ;
    }
};

#endif //LABA3_PERSON_H
