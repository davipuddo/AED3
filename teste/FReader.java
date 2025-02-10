import java.io.*;
import java.util.Scanner;

public class FReader
{
	public static void main(String[] args)
	{	
		try
		{
			FileReader fr = new FileReader("teste.txt");
			BufferedReader br = new BufferedReader(fr);

			String[] data = new String[20];

			int i = 0;
			do
			{
				data[i] = br.readLine();
			} while (i < 20 && data[i++] != null);

			br.close();
			fr.close();
			
			for (i = 0; i < 20; i++)
			{
				if (data[i] != null)
				{
					System.out.println (data[i]);
				}
			}
		}
		catch (IOException ex)
		{
			ex.printStackTrace();
		}
	}
}
