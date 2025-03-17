package entity;

import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.RandomAccessFile;
import java.time.LocalDate;

public class Book implements FileEntity
{
	private int ID;
	private	String ISBN;
	private	String title;
	private	String author;
	private	float price;
	private byte edition;
	private LocalDate date;

	public Book (int i, String isbn, String t, String a, float p, int ed, LocalDate LD)
	{
		this.ID = i;
		this.ISBN = isbn;
		this.title = t;
		this.author = a;
		this.price = p;
		this.edition = (byte)ed;
		this.date = LD;
	}

	public Book (String isbn, String t, String a, float p, int ed, LocalDate LD)
	{
		this(-1, isbn, t, a, p, ed, LD);
	}
	
	public Book ()
	{
		this(-1, "", "", "", 0.0f, 0, LocalDate.now());
	}

	public int getID ()
	{
		return (this.ID);
	}

	public String getTitle()
	{
		return (this.title);
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

		DOS.write(edition);
		DOS.writeInt((int)date.toEpochDay());

		DOS.close();
		BAOS.close();

		return (BAOS.toByteArray());
	}

	public void fromByteArray (byte[] data) throws Exception
	{
		ByteArrayInputStream BAIS = new ByteArrayInputStream(data);

		DataInputStream DIS = new DataInputStream(BAIS);

		this.ID = DIS.readInt();
		byte[] tmp = new byte[13];
		DIS.read(tmp);

		this.title = DIS.readUTF();
		this.author = DIS.readUTF();
		this.price = DIS.readFloat();

		this.ISBN = new String(tmp);

		this.edition = DIS.readByte();
		this.date = LocalDate.ofEpochDay(DIS.readInt());
	}
}
