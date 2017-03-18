
import java.io.FileOutputStream;
import java.io.*;
import java.util.*;
import java.text.Normalizer;
import java.nio.file.*;
/**
 * Created by swati.arora on 3/8/17.
 */
public class ParseDataSet {

    public static void main(String[] args) throws Exception {

        String currDir = System.getProperty("user.dir");
        System.out.println(currDir);
        currDir = currDir.substring(0, currDir.length()-3);
        System.out.println(currDir);
        currDir = currDir + "data";

        //new File(currDir+"../data/Real").mkdir();

        String everything;
        try(BufferedReader br = new BufferedReader(new FileReader(currDir+"/trainingSet.dat"))) {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
                line = br.readLine();
            }
            everything = sb.toString();
        }


        StringTokenizer strings = new StringTokenizer(everything, "~~~~~");
        System.out.println("Tokens are : "+strings.countTokens());

        String[] labels  = new String[1000];
        try(BufferedReader br = new BufferedReader(new FileReader(currDir+"/trainingSetLabels.dat"))) {
            int count = 0;
            String label = br.readLine();
            while(label != null){
                labels[count] = label;
                count++;
                label = br.readLine();
            }
        }
        System.out.println("label array is : "+ Arrays.toString(labels));

        int total_count = 0;
        int fake_count =0;
        int real_count = 0;
        String directory = "";
        String fileName = "";
        while(strings.hasMoreTokens()){

            String entireFileText = strings.nextToken();
            entireFileText = Normalizer.normalize(entireFileText, Normalizer.Form.NFD);
            entireFileText = entireFileText.replaceAll("[^\\x00-\\x7F]", "");
            entireFileText = entireFileText.replaceAll("<.*?> ", "");
            //entireFileText = entireFileText.replaceAll("<.*?>", "").replaceAll("[.,']", "").replaceAll("\t"," ").replaceAll("\n"," ").replaceAll(" +"," ").toLowerCase();
            entireFileText = entireFileText.trim();
            System.out.println("Current label is : " + labels[total_count]);
            if(Integer.parseInt(labels[total_count]) == 1){
                directory = "Real";
                real_count++;
                fileName = String.valueOf(real_count);
                System.out.println("Real docs count is : " + real_count);
            }
            else{
                directory = "Fake";
                fake_count++;
                fileName = String.valueOf(fake_count);
                System.out.println("Fake docs count is : " + fake_count);
            }
            total_count++;

            try(BufferedWriter br = new BufferedWriter(new FileWriter(currDir+"/"+directory+"/"+fileName+".txt"))) {
                br.write(entireFileText);
            }

        }

    }


}
