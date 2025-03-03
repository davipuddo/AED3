#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>

#define byte uint8_t

template <typename T>
class Array
{
	private:
	T* data;
	int n;

	void init (int n)
	{
		this->data = NULL;
		this->n = 0;

		if (n > 0)
		{
			this->data = new T[n];
			this->n = n;
		}
	}

	public:

	Array(int n)
	{
		init(n);
	}

	Array(int n, T df)
	{
		init(n);

		for (int i = 0; i < this->n; i++)
		{
			this->data[i] = df;
		}
	}

	~Array()
	{
		delete(data);
		n = 0;
	}

	void setData (T x, int i)
	{
		if (!data)
		{
			std::cerr << "ERROR: The array is null!\n";
		}
		else if (i < 0 || i >= n)
		{
			std::cerr << "ERROR: The index given is invalid!\n";
		}
		else
		{
			data[i] = x;
		}
	}

	T getData (int i)
	{
		T* res = NULL;

		if (!data)
		{
			std::cerr << "ERROR: The array is null!\n";
		}
		else if (i < 0 || i >= n)
		{
			std::cerr << "ERROR: The index given is invalid!\n";
		}
		else
		{
			res = &data[i];
		}
		return(*res);
	}

	int getSize (void)
	{
		return (this->n);
	}

	Array<T>* clone (void)
	{
		Array<T>* res = NULL;
		if (data)
		{
			// Create new Array
			res = new Array<T>(this->n);
			
			// Copy data
			for (int i = 0; i < this->n; i++)
			{
				res->setData(this->data[i], i);
			}
		}
		return (res);
	}

	void print (char mode)
	{
		if (data && n > 0)
		{
			if (mode == 'c') // Print chars
			{
				for (int i = 0; i < n; i++)
				{
					std::cout << "[" << data[i] << "] ";
				}
			}
			else if (mode == 'h') // Print hexa
			{
				for (int i = 0; i < n; i++)
				{
					printf("[%.2X] ", data[i]);
				}
			}
			std::cout << "\n";
		}
	}

	void print (void)
	{
	
		print('c'); // Define default
	}

};

class DataTypes
{
	private:
	Array<byte>* BA;
	int i;

	public:

	// Constructors
	DataTypes (Array<byte>* other)
	{
		if (other)
		{
			this->BA = other->clone();
			this->i = 0;
		}
	}

	DataTypes (int n)
	{
		if (n > 0)
		{
			this->BA = new Array<byte>(n);
			this->i = 0;
		}
	}
	
	// Distructor
	~DataTypes ()
	{
		delete(BA);
		this->i = 0;
	}
	
	// Methods

	Array<byte>* getByteArray (void)
	{
		Array<byte>* res = NULL;
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else
		{
			res = BA->clone();
		}
		return (res);
	}

	void seek (int i)
	{
		if (i < 0 || i >= BA->getSize())
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Move pointer
			this->i = i;
		}
	}

	int getPointer (void)
	{
		return (i);
	}

	void writeByte (byte x)
	{	
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+1) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Write 1 byte
			BA->setData(x, i++);
		}
	}

	byte readByte (void)
	{
		byte res = 0x00;
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+1) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Read 1 byte
			res = BA->getData(i++);
		}
		return (res);
	}

	void writeInt (int x)
	{
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+4) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Write first byte
			byte buffer = (x & 0xFF000000) >> 24;
			BA->setData(buffer, i++);

			// Write second
			buffer = (x & 0x00FF0000) >> 16;
			BA->setData(buffer, i++);
			
			// Write third
			buffer = (x & 0x0000FF00) >> 8;
			BA->setData(buffer, i++);

			// Write fourth
			buffer = (x & 0x000000FF);
			BA->setData(buffer, i++);
		}
	}

	int readInt (void)
	{
		int res = 0x00000000;
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+4) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Read 4 bytes
			res =  (BA->getData(i++) << 24);
			res += (BA->getData(i++) << 16);
			res += (BA->getData(i++) << 8);
			res += (BA->getData(i++));
		}
		return (res);
	}

	void writeShort (short x)
	{
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+2) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Write upper byte
			byte buffer = (x & 0xFF00) >> 8;
			BA->setData(buffer,i++);

			// Write lower byte
			buffer = (x & 0x00FF);
			BA->setData(buffer, i++);
		}
	}

	short readShort (void)
	{
		short res = 0x0000;
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+2) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Read 2 bytes
			res += (BA->getData(i++) << 8); // Upper
			res += (BA->getData(i++)); 		// Lower
		}
		return (res);
	}

	void writeUTF (const char* str)
	{
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if (!str)
		{
			std::cerr << "ERROR: Invalid string!\n";
		}
		else
		{
			// Get string size
			short strN = (short)strlen(str);

			if ( (i+2+strN) > BA->getSize() )
			{
				std::cerr << "ERROR: Index out of bounds!\n";
			}
			else
			{
				// Write size
				writeShort(strN);
				
				// Write data
				for (int y = 0; y < strN; y++)
				{
					byte buffer = (byte)str[y];
					BA->setData(buffer, i+y);
				}
				i += strN; // Move pointer
			}
		}
	}

	char* readUTF (void)
	{
		char* res = NULL;
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else if ( (i+2) > BA->getSize() )
		{
			std::cerr << "ERROR: Index out of bounds!\n";
		}
		else
		{
			// Read string size
			short strN = readShort();

			if (strN < -1)
			{
				std::cerr << "ERROR: Invalid string size!\n";
			}
			else if ( (i+strN) > BA->getSize() )
			{
				std::cerr << "ERROR: Index out of bounds!\n";
			}
			else
			{
				// Alloc new string
				res = (char*)calloc(strN+1, sizeof(char));

				// Get string data
				for (short y = 0; y < strN; y++)
				{
					res[y] = (char)BA->getData(i+y);
				}
				i += strN; // Move pointer
			}
		}
		return (res);
	}

	void print (void)
	{
		if (BA)
		{
			BA->print('h');
		}
	}

};

class File
{
	private:
	const char* filename;

	public:

	File (const char* const filename)
	{
		if (filename)
		{
			this->filename = filename;
		}
	}

	void write (Array<Array<byte>*>* BAA)
	{
		if (!BAA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else
		{
			// Open stream
			std::ofstream fs;
			fs.open(filename, std::ios::binary | std::ios::out);

			if (!fs)
			{
				std::cerr << "ERROR: the file could not be opened!\n";
			}
			else
			{
				// Get BAA size
				short N = (short)BAA->getSize();
				
				// Store size
				fs << (byte)(N & 0xFF00); // Upper
				fs << (byte)(N & 0x00FF); // Lower

				// Store data
				for (int i = 0; i < N; i++)
				{
					Array<byte>* aux = BAA->getData(i);

					// Get BA size
					short n = aux->getSize();

					// Store size
					fs << (byte)(n & 0xFF00);
					fs << (byte)(n & 0x00FF);
					
					// Store BA data
					for (int y = 0; y < n; y++)
					{
						fs << aux->getData(y);
					}
				}
				fs.close();
			}
		}
	}

	Array<Array<byte>*>* read (void)
	{
		Array<Array<byte>*>* res = NULL;

		// Open stream
		std::ifstream fs;
		fs.open(filename, std::ios::in | std::ios::binary);

		if (!fs)
		{
			std::cerr << "ERROR: The file could not be opened!\n";
		}
		else
		{
			// Define variables
			short N = 0x0000;
			byte tmp = 0x00;

			// Read 1 byte
			fs >> tmp;

			// Shift value
			N = (tmp << 8);

			// Read 1 byte
			fs >> tmp;

			// Add values
			N += tmp;

			// Create ByteArray Array
			res = new Array<Array<byte>*>(N);

			for (int i = 0; i < N; i++)
			{
				// Define
				short n = 0x0000;
				
				// Read
				fs >> tmp;
				
				// Shift
				n = (tmp << 8);
				
				// Read
				fs >> tmp;

				// ADD
				n += tmp;

				// Create ByteArray
				Array<byte>* aux = new Array<byte>(n);

				for (int y = 0; y < n; y++)
				{
					// Define variable
					byte buffer = 0x00;

					// Read 1 byte
					fs.read((char*)&buffer, sizeof(byte));

					// Store value on BA
					aux->setData(buffer, y);
				}

				// Store BA on BAA
				res->setData(aux, i);

			}
			fs.close();
		}
		return (res);
	}
};

class User
{
	private:
	const char* first_name;
	const char* last_name;
	byte age;
	const char* email;
	const char* phone;
	const char* country;

	public:

	// Constructors
	User (const char* first_name, const char* last_name, int age, const char* email, const char* phone, const char* country)
	{
		this->first_name = first_name;
		this->last_name = last_name;
		this->email = email;
		this->phone = phone;
		this->country = country;

		if (age < 0)
		{
			std::cerr << "ERROR: Invalid age!\n";
		}
		else
		{
			this->age = (byte)age;
		}

		if (!isValid())
		{
			std::cerr << "->Constructor\n\n";
		}
	}

	User ()
	{
		this->first_name = NULL;
		this->last_name = NULL;
		this->email = NULL;
		this->phone = NULL;
		this->country = NULL;
		this->age = 0x00;
	}

	// Distructor
	~User (void)
	{
		this->first_name = NULL;
		this->last_name = NULL;
		this->email = NULL;
		this->phone = NULL;
		this->country = NULL;
		this->age = 0x00;
	}

	// Check data
	bool isValid (void)
	{
		bool res = true;
		
		// Check atributes
		if (!first_name)
		{
			std::cerr << "ERROR: First_name is null!\n";
			res = false;
		}
		if (!last_name)
		{
			std::cerr << "ERROR: Last_name is null!\n";
			res = false;
		}
		if (!email)
		{
			std::cerr << "ERROR: Email is null!\n";
			res = false;
		}
		if (!phone)
		{
			std::cerr << "ERROR: Phone is null!\n";
			res = false;
		}
		if (!country)
		{
			std::cerr << "ERROR: Country is null!\n";
			res = false;
		}
		return (res);
	}

	// Get methods //

	const char* getFirst_name (void)
	{
		return(this->first_name);
	}

	const char* getLast_name (void)
	{
		return(this->last_name);
	}

	int getAge (void)
	{
		return(this->age);
	}

	const char* getEmail (void)
	{
		return(this->email);
	}

	const char* getPhone (void)
	{
		return(this->phone);
	}

	const char* getCountry (void)
	{
		return(this->country);
	}

	// Set methods //

	void setFirst_Name (const char* x)
	{
		if (x)
		{
			first_name = x;
		}
	}

	void setLast_Name (const char* x)
	{
		if (x)
		{
			last_name = x;
		}
	}

	void setAge (int x)
	{
		age = x;
	}

	void setEmail (const char* x)
	{
		if (x)
		{
			email = x;
		}
	}

	void setPhone (const char* x)
	{
		if (x)
		{
			phone = x;
		}
	}

	void setCountry (const char* x)
	{
		if (x)
		{
			country = x;
		}
	}

	// Other methods //

	const char* toString (void)
	{
		char* res = NULL;

		if (this->isValid())
		{
			// Concatenate strings
			std::string buffer = "First_Name: ";
			buffer += first_name;

			buffer += "\nLast_Name: ";
			buffer += last_name;

			buffer += "\nAge: ";
			buffer += std::to_string(age);

			buffer += "\nEmail: ";
			buffer += email;

			buffer += "\nPhone: ";
			buffer += phone;

			buffer += "\nCountry: ";
			buffer += country;

			buffer += "";

			// Alloc space
			res = new char[buffer.length()];

			// Copy buffer data
			strcpy(res, buffer.data());
		}
		return (res);
	}

	void print (void)
	{
		std::cout << this->toString() << "\n\n";
	}

	Array<byte>* toByteArray (void)
	{
		Array<byte>* res = NULL;

		if (this->isValid())
		{
			// Get ByteArray size
			int n = (int)strlen(first_name); // +2
			n += (int)strlen(last_name); 	 // +2
			n += (int)strlen(email); 		 // +2
			n += (int)strlen(phone); 		 // +2
			n += (int)strlen(country); 		 // +2
			n += 11; // 10 + 1 (age)

			// Aux class
			DataTypes* DT = new DataTypes(n);

			// Write atributes
			DT->writeUTF(first_name);
			DT->writeUTF(last_name);
			DT->writeByte(age);
			DT->writeUTF(email);
			DT->writeUTF(phone);
			DT->writeUTF(country);

			// Get ByteArray
			res = DT->getByteArray();

			// Free memory
			delete (DT);
		}
		return (res);
	}

	void fromByteArray (Array<byte>* BA)
	{
		if (!BA)
		{
			std::cerr << "ERROR: Invalid data!\n";
		}
		else
		{
			// Aux class
			DataTypes* DT = new DataTypes(BA);

			// Read atributes
			this->first_name = DT->readUTF();
			this->last_name = DT->readUTF();
			this->age = DT->readByte();
			this->email = DT->readUTF();
			this->phone = DT->readUTF();
			this->country = DT->readUTF();

			// Free memory
			delete(DT);
		}
	}

};

void populate ()
{
	// Create users
	std::cout << "===== Normal users =====\n\n";
	User* u1 = new User("Davi", "Puddo", 19, "davifpuddo@gmail.com", "+55 11 1234-5678", "Brazil");
	User* u2 = new User("Davi 2", "Puddo", 19, "davifpuddo@gmail.com", "+55 11 91234-5678", "Brazil");

	// Print users
	u1->print();
	u2->print();

	// Create ByteArray Array
	Array<Array<byte>*>* BAA = new Array<Array<byte>*>(2);
	
	// Add users data
	BAA->setData(u1->toByteArray(), 0);
	BAA->setData(u2->toByteArray(), 1);

	// File aux class
	File* f = new File("log.bin");

	// Write data
	f->write(BAA);

	delete(f);
	delete(BAA);
	delete(u2);
	delete(u1);
}

int main(void)
{	

	// Write data on the file
	//populate();

	// File aux class
	File* f = new File("log.bin");

	// Read data
	Array<Array<byte>*>* BAA = f->read();

	// Create new users from the file data
	User* u1 = new User;
	u1->fromByteArray(BAA->getData(0));

	User* u2 = new User;
	u2->fromByteArray(BAA->getData(1));

	// Print new users
	std::cout << "===== File users =====\n\n";
	u1->print();
	u2->print();

	// Free memory
	delete(u1);
	delete(u2);
	delete(BAA);
	delete(f);

	return (0);
}	
