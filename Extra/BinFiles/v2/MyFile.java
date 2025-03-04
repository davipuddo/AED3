import java.io.RandomAccessFile;
import java.io.File;
import entity.FileEntity;
import java.lang.reflect.Constructor;

public class MyFile<T extends FileEntity> 
{
	public String entityName;
	public RandomAccessFile file;
	public Constructor<T> constructor;
	final int HEADER_SIZE = 13;

	public MyFile (String name, Constructor<T> c) throws Exception
	{
		this.entityName = name;
		this.constructor = c;
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
			file.writeByte(2);	// File ver
			file.writeInt(0);	// last ID
			file.writeLong(-1); // Pointer to the first register
		}
	}

	public int create(T entity) throws Exception
	{
		file.seek(1);	 				// Skip version

		int newID = file.readInt() + 1;
		System.out.println ("newID:"+newID);
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

	public T read (int ID) throws Exception
	{
		T entity = null;
		file.seek(HEADER_SIZE);

		while (file.getFilePointer() < file.length() && entity == null)
		{
			byte lapide = file.readByte();
			short size = file.readShort();
			if (lapide == ' ')
			{
				byte[] data = new byte[size];
				file.read(data);
				T tmp = constructor.newInstance();
				tmp.fromByteArray(data);

				if(tmp.getID() == ID)
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

	public boolean delete (int ID) throws Exception
	{
		boolean status = false;

		long add = 0;
		byte lapide = 0x00;
		short size = 0;
		byte[] data = null;

		file.seek(HEADER_SIZE);
		while (file.getFilePointer() < file.length())
		{
			add = file.getFilePointer();

			lapide = file.readByte();
			size = file.readShort();
			if (lapide == ' ')
			{
				data = new byte[size];

				file.read(data);
				
				T entity = constructor.newInstance();
				entity.fromByteArray(data);

				if (entity.getID() == ID)
				{
					file.seek(add);
					file.writeByte('*');
					status = true;
				}
			}
			else
			{
				file.skipBytes(size);
			}
		}
		return (status);
	}
}
