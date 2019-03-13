

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest()
   {
      //You can use this function to implement your manual testing
      // Documentation: http://commons.apache.org/proper/commons-validator/apidocs/org/apache/commons/validator/routines/UrlValidator.html

       // URLs used for manual testing
       // "http://www.theonion.com/",
       // "https://www.theonion.com/",
       // "http:/www.theonion.com/",
       // "http:www.theonion.com/",
       // "https://www.theonion.com:65535",
       // "https://www.theonion.com:0",
       // "https://www.theonion.com:999999999999",
       // "https://www.theonion.com:-1",
       // "https://www.theonion.com:30A0",
       // "https://www.theonion.com:65536",
       // "https://www.theonion.com:65535/local",
       // "https://www.theonion.com/local",
       // "https://www.theonion.com:65535/local/sports",
       // "https://www.theonion.com/search?q=biden",
       // "ftp://www.theonion.com/",
       // "ftp://www.theonion.com:65535",
       // "ftp://www.theonion.com:65536",
       // "ftp://www.theonion.com:65535/local",
       // "ftp://www.theonion.com/local",
       // "ftp://www.theonion.com:65535/local/sports",
       // "ftp://www.theonion.com/search?q=biden",
       // "http://localhost",
       // "http://localhost:3000",
       // "http://localhost/test1",
       // "http://localhost/test1/test2",
       // "http://localhost:3000/test1",
       // "http://localhost:3000/test1/test2",
       // "aaa://test.net",
       // "file:///C:/test.txt",
       // "file://C:/test.txt",
       // "HTTPS://www.theonion.com/",
       // "HTTP://www.theonion.com/",
       // "https://test.theonion.com/",
       // "http://www.test.com/thing#place"

      String url = "https://www.theonion.com";

      System.out.println("Manual Testing UrlValidator.isValid()");

      // Test default UrlValidator()
      UrlValidator urlVal1 = new UrlValidator();
      System.out.println("----------OPTIONS: default--------");
      if(urlVal1.isValid(url)){
         System.out.println("VALID: " + url);
      }
      else {
         System.out.println("NOT VALID: " + url);
      }

      // Test each option individually UrlValidator(long option)
      long opt1 = UrlValidator.ALLOW_2_SLASHES;
      UrlValidator urlVal2 = new UrlValidator(null, null, opt1);
      System.out.println("--------OPTIONS: ALLOW_2_SLASHES--------");
      if(urlVal2.isValid(url)){
         System.out.println("VALID: " + url);
      }
      else {
         System.out.println("NOT VALID: " + url);
      }


      long opt2 = UrlValidator.ALLOW_LOCAL_URLS;
      UrlValidator urlVal3 = new UrlValidator(null, null, opt2);
      System.out.println("--------OPTIONS: ALLOW_LOCAL_URLS--------");
      if(urlVal3.isValid(url)){
         System.out.println("VALID: " + url);
      }
      else {
         System.out.println("NOT VALID: " + url);
      }


      long opt3 = UrlValidator.NO_FRAGMENTS;
      UrlValidator urlVal4 = new UrlValidator(null, null, opt3);
      System.out.println("--------OPTIONS: NO_FRAGMENTS--------");
      if(urlVal4.isValid(url)){
         System.out.println("VALID: " + url);
      }
      else {
         System.out.println("NOT VALID: " + url);
      }


      long opt4 = UrlValidator.ALLOW_ALL_SCHEMES;
      UrlValidator urlVal5 = new UrlValidator(null, null, opt4);
      System.out.println("--------OPTIONS: ALLOW_ALL_SCHEMES--------");
      try {
         if (urlVal5.isValid(url)) {
            System.out.println("VALID: " + url);
         } else {
            System.out.println("NOT VALID: " + url);
         }
      }
      catch(ExceptionInInitializerError|NoClassDefFoundError e){
         System.out.println("ERROR!!! " + e.getMessage() + " while testing " + url);
      }


      // Test with all options used at once UrlValidator(long options)
      long opt5 = UrlValidator.ALLOW_ALL_SCHEMES +
              UrlValidator.ALLOW_2_SLASHES +
              UrlValidator.NO_FRAGMENTS +
              UrlValidator.ALLOW_LOCAL_URLS;
      UrlValidator urlVal6 = new UrlValidator(null, null, opt5);
      System.out.println("--------OPTIONS: ALLOW_ALL_SCHEMES + ALLOW_2_SLASHES + NO_FRAGMENTS + ALLOW_LOCAL_URLS--------");
      try {
         if (urlVal6.isValid(url)) {
            System.out.println("VALID: " + url);
         } else {
            System.out.println("NOT VALID: " + url);
         }
      }
      catch(ExceptionInInitializerError|NoClassDefFoundError e){
         System.out.println("ERROR!!! " + e.getMessage() + " while testing " + url);
      }


      // Test with schemes specified UrlValidator(String [] schemes)
      String[] schemes = {"http"};
      UrlValidator urlVal7 = new UrlValidator(schemes);
      System.out.println("----------SCHEMES: http--------");
      if(urlVal7.isValid(url)){
         System.out.println("VALID: " + url);
      }
      else {
         System.out.println("NOT VALID: " + url);
      }


      // Test with regex for authority UrlValidator(RegexValidator authorityValidator)
      RegexValidator regex = new RegexValidator("test.theonion.com");
      UrlValidator urlVal8 = new UrlValidator(regex, 0);
      System.out.println("----------REGEX AUTHORITY VALIDATOR: test.theonion.com--------");
      if(urlVal8.isValid(url)){
         System.out.println("VALID: " + url);
      }
      else {
         System.out.println("NOT VALID: " + url);
      }

   }


   public void testRandomUrlValidatorTest()
   {
	 //You can use this function to implement your First Partition testing
      int randomRuns = 100;
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
//    UrlValidator urlVal = new UrlValidator();

      //For loop to assemble a random url
      // <scheme>://<authority><path>?<query> except that the port number
      Random rand = new Random(98);
      for(int ii=0; ii < randomRuns; ii++) {

         String testUrl = "";
         boolean allValid = true;

         int randInt = rand.nextInt(testUrlScheme.length);

         testUrl += testUrlScheme[randInt].item ;
         allValid &= testUrlScheme[randInt].valid ;

         randInt = rand.nextInt(testUrlAuthority.length);
         testUrl += testUrlAuthority[randInt].item ;
         allValid&= testUrlAuthority[randInt].valid ;

         int portNum = rand.nextInt(80000);
         if(portNum <= 65535) {
            allValid &= true;
            testUrl += ":"+Integer.toString(portNum);
         } else if (portNum < 70000) {
            allValid &= false;
            testUrl += ":"+Integer.toString(portNum);
         } else {
            allValid &= true;
         }

         randInt = rand.nextInt(testPath.length);
         testUrl += testPath[randInt].item ;
         allValid &= testPath[randInt].valid ;

         randInt = rand.nextInt(testUrlPathOptions.length);
         testUrl += testUrlPathOptions[randInt].item ;
         allValid &= testUrlPathOptions[randInt].valid ;

         randInt = rand.nextInt(testUrlQuery.length);
         testUrl += testUrlQuery[randInt].item ;
         allValid &= testUrlQuery[randInt].valid ;

         System.out.print(testUrl+" ");

/*        boolean result = urlVal.isValid(testUrl);
       if(result == allValid ){
        	System.out.print("			Test Passed.\n");
        }else {
        	System.out.print("			Test FAILED.\n");
        }
    */    try {
            boolean result = urlVal.isValid(testUrl);

            if(result == allValid ){
               System.out.print("			Test Passed.");
               if(allValid ) {
                  System.out.print(" URL was Valid\n");
               } else {
                  System.out.print(" URL was invalid\n");
               }
            }else {
               System.out.print("			Test FAILED.");
               if(allValid ) {
                  System.out.print(" URL was Valid\n");
               } else {
                  System.out.print(" URL was invalid\n");
               }
            }
         } catch(Throwable e) {
            System.out.print("			Test FAILED due to exception or error. ");
            if(allValid ) {
               System.out.print("URL was Valid\n");
            } else {
               System.out.print("URL was invalid\n");
            }
            System.out.print(e+"\n");
         }
      }


   }
   /*
static ResultPair[] testUrlScheme = {new ResultPair("http://", true),
		new ResultPair("https://", true)
        //new ResultPair("g@rba&e!", false)
        };

static ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
				new ResultPair("www.yahoo.com", true)
};

static ResultPair[] testPath = {
   new ResultPair("", true)
};
static ResultPair[] testUrlPathOptions = {
             new ResultPair("", true)
};

static ResultPair[] testUrlQuery = {       new ResultPair("", true)
};

*/   //Many of these result pairs are taken from the original UrlValidatorTest code, some have been added and removed from the sets
   static ResultPair[] testUrlScheme = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("https://", true),
           new ResultPair("HTTPS://", true),
           new ResultPair("FTP://", true),
           new ResultPair("HTTP://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("g@rba&e!", false),
           new ResultPair("", true)};

   static ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
           new ResultPair("www.yahoo.com", true),
           new ResultPair("go.com", true),
           new ResultPair("go.au", true),
           new ResultPair("0.0.0.0", true),
           new ResultPair("255.255.255.255", true),
           new ResultPair("256.256.256.256", false),
           new ResultPair("255.com", true),
           new ResultPair("1.2.3.4.5", false),
           new ResultPair("1.2.3.4.", false),
           new ResultPair("1.2.3", false),
           new ResultPair(".1.2.3.4", false),
           new ResultPair("go.a", false),
           new ResultPair("go.a1a", false),
           new ResultPair("go.1aa", false),
           new ResultPair("aaa.", false),
           new ResultPair(".aaa", false),
           new ResultPair("aaa", false),
           new ResultPair("G'Day", false),
           new ResultPair("", false)
   };

   static ResultPair[] testPath = {new ResultPair("/test1", true),
           new ResultPair("/t123", true),
           new ResultPair("/$23", true),
           new ResultPair("/..", false),
           new ResultPair("/../", false),
           new ResultPair("/test1", true),
           new ResultPair("", true),
           new ResultPair("/test1/file", true),
           new ResultPair("/..//file", false),
           new ResultPair("/test1//file", false)
   };
   static ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
           new ResultPair("/t123", true),
           new ResultPair("/$23", true),
           new ResultPair("/..", false),
           new ResultPair("/../", false),
           new ResultPair("/test1/", true),
           new ResultPair("/#", false),
           new ResultPair("", true),
           new ResultPair("/test1/file", true),
           new ResultPair("/t123/file", true),
           new ResultPair("/$23/file", true),
           new ResultPair("/../file", false),
           new ResultPair("/..//file", false),
           new ResultPair("/test1/file", true),
           new ResultPair("/#/file", false)
   };

   static ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("", true)
   };


   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing

   }
   //You need to create more test cases for your Partitions if you need to

   public void testIsValid()
   {
	   //You can use this function for programming based testing
      //You can use this function for programming based testing
      UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

      String validAuthorityHttp = "http://www.google.com";
      //String validAuthorityHttps = "https://www.google.com";
      //String validAuthorityFtp = "ftp://www.google.com";
      String validPort = ":80";
      String validPath = "/test";

      String invalidAuthority = "http://badauth";
      String invalidPort = ":99999";
      String invalidPath = "/..";

      String[] validPartsHttp = {validAuthorityHttp, validPort, validPath};
      //String[] validPartsHttps = {validAuthorityHttps, validPort, validPath};
      //String[] validPartsFtp = {validAuthorityFtp, validPort, validPath};
      String[] invalidParts = {invalidAuthority, invalidPort, invalidPath};

      StringBuilder urlBuffer = new StringBuilder();

      System.out.println("Valid HTTP URL combination tests:");
      // Test combinations of valid URLs with http scheme
      for(int i = 0; i < 3; i++)
      {
         urlBuffer.append(validPartsHttp[i]);
         System.out.println(urlBuffer + " should be VALID");
         //assertTrue(urlVal.isValid(urlBuffer.toString()));
         if (urlVal.isValid(urlBuffer.toString())) {
            System.out.println("isValid() says: VALID");
            System.out.println();
         } else {
            System.out.println("isValid() says: INVALID");
            System.out.println();
         }
      }

      // Clear buffer
      urlBuffer.setLength(0);

	   /* THESE TESTS CAUSE EXCEPTION ERRORS
	   System.out.println("Valid HTTPS URL combination tests:");
	   // Test combinations of valid URLs with https scheme
	   for(int i = 0; i < 3; i++)
	   {
		   urlBuffer.append(validPartsHttps[i]);
		   System.out.println(urlBuffer + " should be VALID");
		   //assertTrue(urlVal.isValid(urlBuffer.toString()));
		   if (urlVal.isValid(urlBuffer.toString())) {
			   System.out.println("isValid() says: VALID");
			   System.out.println();
		   } else {
			   System.out.println("isValid() says: INVALID");
			   System.out.println();
		   }
	   }

	   // Clear buffer
	   urlBuffer.setLength(0);

	   System.out.println("Valid FTP URL combination tests:");
	   // Test combinations of valid URLs with ftp scheme
	   for(int i = 0; i < 3; i++)
	   {
		   urlBuffer.append(validPartsFtp[i]);
		   System.out.println(urlBuffer + " should be VALID");
		   //assertTrue(urlVal.isValid(urlBuffer.toString()));
		   if (urlVal.isValid(urlBuffer.toString())) {
			   System.out.println("isValid() says: VALID");
			   System.out.println();
		   } else {
			   System.out.println("isValid() says: INVALID");
			   System.out.println();
		   }
	   }

	   // Clear buffer
	   urlBuffer.setLength(0);
	    */

      System.out.println("Invalid URL combination tests:");
      // Test comibinations of invalid URLs
      for(int i = 0; i < 3; i++)
      {
         urlBuffer.append(invalidParts[i]);
         System.out.println(urlBuffer + " should be INVALID");
         if (urlVal.isValid(urlBuffer.toString())) {
            System.out.println("isValid() says: VALID");
            System.out.println();
         } else {
            System.out.println("isValid() says: INVALID");
            System.out.println();
         }
      }

      // Clear buffer
      urlBuffer.setLength(0);

      // Test empty port
      System.out.println("No port test:");
      urlBuffer.append(validAuthorityHttp);
      urlBuffer.append(validPath);
      System.out.println(urlBuffer + " should be VALID");
      if (urlVal.isValid(urlBuffer.toString())) {
         System.out.println("isValid() says: VALID");
         System.out.println();
      } else {
         System.out.println("isValid() says: INVALID");
         System.out.println();
      }

      // Clear buffer
      urlBuffer.setLength(0);

      // Test invalid port
      System.out.println("Invalid port test:");
      urlBuffer.append(validAuthorityHttp);
      urlBuffer.append(invalidPort);
      System.out.println(urlBuffer + " should be INVALID");
      if (urlVal.isValid(urlBuffer.toString())) {
         System.out.println("isValid() says: VALID");
         System.out.println();
      } else {
         System.out.println("isValid() says: INVALID");
         System.out.println();
      }

      // Clear buffer
      urlBuffer.setLength(0);

      // Test invalid path
      System.out.println("Invalid path test:");
      urlBuffer.append(validAuthorityHttp);
      urlBuffer.append(invalidPath);
      System.out.println(urlBuffer + " should be INVALID");
      if (urlVal.isValid(urlBuffer.toString())) {
         System.out.println("isValid() says: VALID");
         System.out.println();
      } else {
         System.out.println("isValid() says: INVALID");
         System.out.println();
      }

      // Clear buffer
      urlBuffer.setLength(0);

      UrlValidator urlValNoOpt = new UrlValidator();

      // Test default URL validator option
      System.out.println("Valid URL combination tests under default options:");
      for(int i = 0; i < 3; i++)
      {
         urlBuffer.append(validPartsHttp[i]);
         System.out.println(urlBuffer + " should be VALID");
         //assertTrue(urlVal.isValid(urlBuffer.toString()));
         if (urlValNoOpt.isValid(urlBuffer.toString())) {
            System.out.println("isValid() says: VALID");
            System.out.println();
         } else {
            System.out.println("isValid() says: INVALID");
            System.out.println();
         }
      }

      // Clear buffer
      urlBuffer.setLength(0);

      String[] schemes = {"http","https", "test"};
      UrlValidator urlValCustomScheme = new UrlValidator(schemes);

      // Test default URL validator option
      System.out.println("Valid URL combination tests using custom schemes:");
      for(int i = 0; i < 3; i++)
      {
         urlBuffer.append(validPartsHttp[i]);
         System.out.println(urlBuffer + " should be VALID");
         //assertTrue(urlVal.isValid(urlBuffer.toString()));
         if (urlValCustomScheme.isValid(urlBuffer.toString())) {
            System.out.println("isValid() says: VALID");
            System.out.println();
         } else {
            System.out.println("isValid() says: INVALID");
            System.out.println();
         }
      }

      // Clear buffer
      urlBuffer.setLength(0);

      // Test custom scheme
      System.out.println("Custom scheme test:");
      urlBuffer.append("test://www.google.com");
      urlBuffer.append(validPath);
      System.out.println(urlBuffer + " should be VALID");
      if (urlValCustomScheme.isValid(urlBuffer.toString())) {
         System.out.println("isValid() says: VALID");
         System.out.println();
      } else {
         System.out.println("isValid() says: INVALID");
         System.out.println();
      }

   }
   


}
