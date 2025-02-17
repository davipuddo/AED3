import java.io.RandomAccessFile;
import java.io.File;
import book.Book;

public class MyFile
{
	public String entityName;
	public RandomAccessFile file;
	final int HEADER_SIZE = 13;

	public MyFile (String name) throws Exception
	{
		this.entityName = name;
		File f = new File (".//data//");
		if (!f.exists())
		{
			f.mkdir();
		}
		f = new File (".//data//"+entityName);
		if (!f.exists())
		{
			f.mkdir();
		}
		file = new RandomAccessFile (".//data//"+entityName+"//"+entityName+".db", "rw");

		if (file.length() < HEADER_SIZE);
		{
			file.writeByte(1);	// File ver
			file.writeInt(0);	// last ID
			file.writeLong(-1); // Pointer to the first register
		}
	}

	public int create(Book entity) throws Exception
	{
		file.seek(1);	 				// Skip version

		int newID = file.readInt() + 1;
		entity.setID(newID);			// Set new ID

		file.seek(1);
		file.writeInt(newID);

		// Write new register
		file.seek(file.length());
		file.writeByte(' ');
		
		byte[] data = entity.toByteArray();
		file.writeShort(data.length);
		file.write(data);

		return (newID);
	}

	public Book read (String ISBN) throws Exception
	{
		Book entity = null;
		file.seek(HEADER_SIZE);

		while (file.getFilePointer() < file.length() && entity == null)
		{
			byte lapide = file.readByte();
			short size = file.readShort();
			if (lapide == ' ')
			{
				byte[] data = new byte[size];
				file.read(data);

				Book tmp = new Book();
				tmp.fromByteArray(data);

				if(ISBN.equals(tmp.getISBN()))
				{
					entity = tmp;
				}
			}
			else
			{
				file.skipBytes(size);
			}
		}
		return (entity);
	}
}
