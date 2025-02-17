package book;

import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.RandomAccessFile;

public class Book implements FileEntity
{
	private int ID;
	private	String ISBN;
	private	String title;
	private	String author;
	private	float price;

	public Book (int i, String isbn, String t, String a, float p)
	{
		this.ID = i;
		this.ISBN = isbn;
		this.title = t;
		this.author = a;
		this.price = p;
	}

	public Book (String isbn, String t, String a, float p)
	{
		this(-1, isbn, t, a, p);
	}
	
	public Book ()
	{
		this(-1, "", "", "", 0F);		
	}

	public int getID ()
	{
		return (this.ID);
	}

	public void setID (int x)
	{
		this.ID = x;
	}

	public String getISBN ()
	{
		return (this.ISBN);
	}

	public byte[] toByteArray() throws Exception
	{
		ByteArrayOutputStream BAOS = new ByteArrayOutputStream();

		DataOutputStream DOS = new DataOutputStream(BAOS);

		DOS.writeInt(ID);

		DOS.write (ISBN.getBytes());

		DOS.writeUTF (title);
		DOS.writeUTF (author);

		DOS.writeFloat (price);

		DOS.close();
		BAOS.close();

		return (BAOS.toByteArray());
	}

	public void fromByteArray (byte[] data) throws Exception
	{
		ByteArrayInputStream BAIS = new ByteArrayInputStream(data);

		DataInputStream DIS = new DataInputStream(BAIS);

		this.ID = DIS.readInt();
		this.author = DIS.readUTF();
		this.title = DIS.readUTF();
		this.price = DIS.readFloat();

		byte[] tmp = new byte[13];
		DIS.read(tmp);

		this.ISBN = new String(tmp);
	}
}
