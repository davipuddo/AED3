import entity.Book;
import java.time.LocalDate;

public class Main 
{
	public static void main(String[] args)
	{	
		try
		{
			MyFile<Book> BookFile = new MyFile<>("Books", Book.class.getConstructor());
			//populate(BookFile);

			Book l = BookFile.read(2);
			if(l != null)
			{
				System.out.println (l.getTitle());
			}
			l = BookFile.read(1);
			if (l != null)
			{
				System.out.println (l.getTitle());
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	public static void populate (MyFile file) throws Exception
	{
		Book l1 = new Book ("123456789ABCD", "Titulo1", "Autor", 50.0F, 1, LocalDate.now());
		Book l2 = new Book ("23456789ABCD1", "Titulo2", "Autor", 22.5F, 2, LocalDate.now());
		file.create(l1);
		file.create(l2);
	}
}
