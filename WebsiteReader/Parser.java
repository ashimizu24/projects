package ashimizu_CSCI201_HW2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.logging.Level;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.http.Part;

import com.google.gson.Gson;

import json_files.MainClass;


/**
 * Servlet implementation class Parser
 */
@WebServlet("/Parser")
@MultipartConfig

public class Parser extends HttpServlet {
	private static final long serialVersionUID = 1L;
  
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		
		String path = request.getParameter("file");
	    Part filePart = request.getPart("file");
	    final String fileName = getFileName(filePart);
	    System.out.println(fileName);

	    InputStream filecontent = null;
	    Reader reader = null;
		BufferedReader br = null;
		
		MainClass school = null;
		Gson gson = new Gson();
		
		try {
			filecontent = filePart.getInputStream();
			reader = new InputStreamReader(filecontent);
			br = new BufferedReader(reader); 
		
			try {
				
				school = gson.fromJson(br, MainClass.class);
				System.out.println("array size: " + school.getSchools().size());
				
				HttpSession session = request.getSession();
				session.setMaxInactiveInterval(60);
				session.setAttribute("schools", school);
				
				RequestDispatcher dispatch = request.getRequestDispatcher("/Home.jsp");
				dispatch.forward(request, response);
				
			}
			catch(IOException jpe) {
				System.out.println("File parsing error" + jpe.getMessage());
			}
			
			
		}
		catch(FileNotFoundException fnfe) {
			System.out.println("File not found " + fnfe.getMessage());
		}
		catch(IOException ioe) {
			System.out.println("File error " + ioe.getMessage());
		}
		finally {
			if(br != null) {
				try {
					br.close();
				} catch(IOException ioe) {
					System.out.println("File error " + ioe.getMessage());
				}
			}
			if(reader != null) {
				try {
					reader.close();
				} catch(IOException ioe) {
					System.out.println("File error " + ioe.getMessage());
				}
			}
		}
		
		
	
	}
	private String getFileName(final Part part) {
	    final String partHeader = part.getHeader("content-disposition");
	    for (String content : part.getHeader("content-disposition").split(";")) {
	        if (content.trim().startsWith("filename")) {
	            return content.substring(
	                    content.indexOf('=') + 1).trim().replace("\"", "");
	        }
	    }
	    return null;
	}
}
