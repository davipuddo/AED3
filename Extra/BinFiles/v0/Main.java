// Davi Ferreira Puddo

import java.io.*;

// Data class
class User 
{
	// Atributes
	private String name;
	private int age;
	
	// Constructor
	public User (String n, int x)
	{
		name = n;
		age = x;
	}

	// ---
	public User ()
	{
		this(null, 0);
	}

	// Convert user atributes to a byte array
	public byte[] toBytes() throws IOException
	{
		// Create byte array os
		ByteArrayOutputStream BAOS = new ByteArrayOutputStream();

		// Use Data Stream for more data types
		DataOutputStream DOS = new DataOutputStream(BAOS);
		
		// Write user elements
		DOS.writeUTF(this.name);
		DOS.writeInt(this.age);

		// Close streams
		DOS.close();
		BAOS.close();

		return (BAOS.toByteArray());
	}

	// Set user atributes from a byte array
	public void fromBytes(byte[] data) throws IOException
	{
		// Create byte array is
		ByteArrayInputStream BAIS = new ByteArrayInputStream(data);

		// User Data Stream for more data types
		DataInputStream DIS = new DataInputStream(BAIS);

		// Read user elements
		this.name = DIS.readUTF();
		this.age = DIS.readInt();

		// Close streams
		DIS.close();
		BAIS.close();
	}

	// Stringfy user atributes
	public String toString ()
	{
		return ("Name:"+this.name+"\nAge:"+this.age);
	}

}

// File management class
class File
{
	public File ()
	{}

	// Write a byte array to a file
	public static void writeFile (byte[] data, String filename)
	{
		try
		{
			// Create file out stream
			FileOutputStream FOS = new FileOutputStream(filename);

			// Use data stream for more data types
			DataOutputStream DOS = new DataOutputStream(FOS);
			
			// Write byte array size
			DOS.writeInt(data.length);

			// Write byte array
			DOS.write(data);

			// Close streams
			DOS.close();
			FOS.close();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}

	// Read a byte array from a file
	public static byte[] readFile (String filename)
	{
		byte[] res = null;
		try
		{
			// Create file in stream
			FileInputStream FIS = new FileInputStream(filename);

			// Use data stream for more data types
			DataInputStream DIS = new DataInputStream (FIS);

			// Read byte array size
			int n = DIS.readInt();

			// Create new byte array
			res = new byte[n];

			// Copy bytes from file
			FIS.read(res);

			// Close streams
			DIS.close();
			FIS.close();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
		return (res);
	}
}

// Test class
public class Main
{
	public static void main(String[] args)
	{	
		// Define variables
		User u1 = null;
		User u2 = null;
		byte[] bytes = null;

		// Create users
		u1 = new User("Davi", 19);
		u2 = new User();

		try
		{
			// Read u1 bytes
			bytes = u1.toBytes();

			// Write bytes in a file
			File.writeFile(bytes, "user.bin");

			// 'Clear' data
			bytes = null;

			// Read bytes from the file
			bytes = File.readFile("user.bin");

			// Define u2 values from the byte array
			u2.fromBytes(bytes);
			
			// Print users
			System.out.println ("u1:\n"+u1);
			System.out.println ("u2:\n"+u2);
			
			/* user.bin: [00 00 00 0A 00 04 44 61 76 69 00 00 00 13 0A]

				|00 00 00 0A| -> byte array size (10)
				|00 04| -> String size
				|44| -> 'D'
				|61| -> 'a'
				|76| -> 'v'
				|69| -> 'i'
				|00 00 00 13| -> age (19)
				|0A| -> [new line]
			*/
		}
		catch (IOException ex)
		{
			ex.printStackTrace();
		}
	}
}
