package transformationTest;

import java.io.*;

public class CreateMakefile {
	
	public CreateMakefile(){}
	
	public void createFiles(String path){
		
		try {
			BufferedWriter hepsycode_makefile = new BufferedWriter(new FileWriter(path + "Makefile"));
			hepsycode_makefile.append(XGeneratorLib.createMakefile());
			hepsycode_makefile.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			BufferedWriter hepsycode_makefile = new BufferedWriter(new FileWriter(path + "settings.sh"));
			hepsycode_makefile.append(XGeneratorLib.createSettings());
			hepsycode_makefile.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
