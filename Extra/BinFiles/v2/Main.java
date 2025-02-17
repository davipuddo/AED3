import book.Book;

public class Main 
{
	public static void main(String[] args)
	{	
		try
		{
			MyFile BookFile = new MyFile ("Books");

			Book l1 = new Book ("123456789ABCD", "Titulo1", "Autor", 0F);
			Book l2 = new Book ("23456789ABCD1", "Titulo2", "Autor", 0F);

			BookFile.create(l1);
			BookFile.create(l2);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}
