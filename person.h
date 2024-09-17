#ifndef __PERSON_H
#define __PERSON_H

class Person
{
protected:
	char* firstName;
	char* lastName;

	Person(const char* firstName, const char* lastName);
	Person(const Person& other);
	Person(const Person&& other);

public:
	virtual ~Person();
	
	const Person& operator=(const Person& other);
	const Person& operator=(Person&& other) noexcept;

	const char* getFirstName() const;
	void setFirstName(const char* firstName);
	const char* getLastName() const;
	void setLastName(const char* lastName);
	virtual void print() const = 0;
};

#endif // __PERSON_