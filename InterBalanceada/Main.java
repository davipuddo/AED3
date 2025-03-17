import java.io.*;

class User
{
	private int ID;
	private String name;
	private int age;

	public User (int ID, String name, int age)
	{
		this.ID = ID;
		this.name = name;
		this.age = age;
	}

	public User (String name, int age)
	{
		this(-1, name, age);
	}

	public User ()
	{
		this (-1, "", -1);
	}

	public void setID (int ID)
	{
		this.ID = ID;
	}

	public int getID ()
	{
		return (this.ID);
	}

	public String toString ()
	{
		return ("ID: "+ID+"\nName: "+name+"\nAge: "+age+"\n");
	}

	public byte[] toByteArray () throws Exception
	{
		ByteArrayOutputStream BAOS = new ByteArrayOutputStream();
		DataOutputStream DOS = new DataOutputStream(BAOS);

		DOS.writeInt(ID);
		DOS.writeUTF(name);
		DOS.writeInt(age);

		return (BAOS.toByteArray());
	}

	public void fromByteArray(byte[] BA) throws Exception
	{
		ByteArrayInputStream BAIS = new ByteArrayInputStream(BA);
		DataInputStream DIS = new DataInputStream (BAIS);

		this.ID = DIS.readInt();
		this.name = DIS.readUTF();
		this.age = DIS.readInt();
	}
}

class MyFile
{
	private RandomAccessFile RAF;

	public MyFile (String filename) throws Exception
	{
		File f = new File (".//data//");
		
		if (!f.exists())
		{
			f.mkdir();
		}
		RAF = new RandomAccessFile (".//data//"+filename+".db", "rw");

		if (RAF.length() < 4)
		{
			RAF.writeInt(0);
		}
	}

	public void create (User U) throws Exception
	{
		RAF.seek(0);

		int newID = RAF.readInt() + 1;
		U.setID(newID);

		RAF.seek(0);
		RAF.writeInt(newID);

		RAF.seek(RAF.length());

		byte[] BA = U.toByteArray();

		RAF.writeShort(BA.length);
		RAF.write(BA);
	}

	public User read (int ID) throws Exception
	{
		User res = null;
		if (ID < 1)
		{
			System.out.println ("ERROR: Invalid ID!");
		}
		else
		{
			RAF.seek(4); // Skip header
			while (RAF.getFilePointer() < RAF.length() && res == null)
			{
				short size = RAF.readShort();
				byte[] BA = new byte[size];

				RAF.read(BA);

				User tmp = new User();

				tmp.fromByteArray(BA);

				if (tmp.getID() == ID)
				{
					res = tmp;
				}
			}
		}
		return (res);
	}
}

public class Main
{
	public static void populate () throws Exception
	{
		User u1 = new User("davi", 19);
		User u2 = new User("ivad", 91);
		User u3 = new User("vadi", 20);
		User u4 = new User("avid", 02);

		MyFile f = new MyFile("u");

		f.create(u1);
		f.create(u2);
		f.create(u3);
		f.create(u4);
	}

	public static void main(String[] args)
	{	
		try
		{
			//populate();

			MyFile f = new MyFile("u");

			System.out.println (f.read(16).toString());
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}
