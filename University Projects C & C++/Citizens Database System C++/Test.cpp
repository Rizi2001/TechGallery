#include "gtest/gtest.h"
#include "Header.h"

TEST(SearchTest, CBID) {
  
	Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    string s1="joe frank m 44 downing street british murder life in prison - 123456 Vodafone 12/04/2010 12/04/2020 unactive";
    
    EXPECT_TRUE(db.CBID_Search_by_CNIC(3740)==s1);

}

TEST(SearchTest, CCID) {
  
    Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    string s1="Halsey Palmer f 11 Ann Street british burglary 6 years in prison 7000 323485 EE 12/12/2017 12/12/2027 active";
    
    EXPECT_TRUE(db.CCID_Search_by_CNIC(5960)==s1);

}

TEST(SearchTest, CCND) {
  
    Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    string s1="Hollace Dudley f 1 Ann Street british 423470 Skymobile 12/1/2000 12/1/2010 unactive";
    
    EXPECT_TRUE(db.CCND_Search_by_CNIC(6287)==s1);

}


TEST(UpdateTest, CBID_Name) {

	Database db("CBID.txt", "CCID.txt", "CCND.txt");
	
    EXPECT_TRUE(db.updateCBIDName("Alice",9831)==1);
    EXPECT_TRUE(db.updateCBIDName("Doc",9832)==0);
    
}

TEST(UpdateTest, CBID_FName) {

    Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    EXPECT_TRUE(db.updateCBIDFName("Kevin",9177)==1);
    EXPECT_TRUE(db.updateCBIDFName("Steve",1234)==0);
    
}

TEST(UpdateTest, CBID_Address) {

    Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    EXPECT_TRUE(db.updateCBIDAddress("12 Ann Street",8372)==1);
    EXPECT_TRUE(db.updateCBIDAddress("21 Downing Street",9639)==0);
    
}

TEST(UpdateTest, CBID_Nationality) {

    Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    EXPECT_TRUE(db.updateCBIDNationality("Alien",8000)==1);
    EXPECT_TRUE(db.updateCBIDNationality("Alien",9832)==0);
    
}

TEST(CrimeAddTest, CCID) {

    Database db("CBID.txt", "CCID.txt", "CCND.txt");

    EXPECT_TRUE(db.addCrime(7564,"Robbery", "2 years in prison","1000")==1);
    
    EXPECT_TRUE(db.addCrime(8099,"Kidnapping", "20 years in prison","2000")==0);
}


TEST(CrimeDeleteTest, CCID) {

    Database db("CBID.txt", "CCID.txt", "CCND.txt");

    EXPECT_TRUE(db.deleteCrime(5960,"burglary", "6 years in prison","7000")==1);
    
    EXPECT_TRUE(db.deleteCrime(4064,"murder", "2 years in prison","10000")==0);
}

TEST(CrimeUpdateTest, CCID) {

    Database db("CBID.txt", "CCID.txt", "CCND.txt");

    EXPECT_TRUE(db.updateCrime(5960,"murder", "20 years in prison","10000")==1);
    
    EXPECT_TRUE(db.updateCrime(9630,"murder", "20 years in prison","10000")==0);
}

TEST(addNumber, CCND) {
/*Aslo try adding 5th number in database against CNIC, it should limit to max 4 numbers. Refer to CCND point 'v'*/
    Database db("CBID.txt", "CCID.txt", "CCND.txt");
    
    ASSERT_TRUE(db.addNumber(9630,123480) == 2);

}



TEST(checkRegistred_No, CCND) {

	Database db("CBID.txt", "CCID.txt", "CCND.txt");
	
    ASSERT_TRUE(db.checkRegistred_No(4305) == 4);
    
    ASSERT_TRUE(db.checkRegistred_No(9662) == 1);
    
    ASSERT_TRUE(db.checkRegistred_No(9630) == 0);

}

/*
TEST(PrintCount, CCND) {

	Database db("CBID.txt", "CCID.txt", "CCND.txt");

    ASSERT_TRUE(db.printcount() == 54);

}
*/