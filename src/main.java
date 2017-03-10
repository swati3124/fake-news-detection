import java.io.*;
import java.util.*;

import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.ParseException;
import org.json.simple.parser.JSONParser;
/**
 * Created by mitshubh on 3/7/17.
 */

public class main {
    public static void main(String[] args) throws Exception {
        List<String> urlList = new ArrayList<>();
        //Global Dictionary
        Map<String, String> dict = new HashMap<>();
        Map<String, Integer> subDict = new HashMap<>();
        Map<String, Integer> objDict = new HashMap<>();
        Map<String, Set<String>> kBase = new HashMap<>();
        int subCount=0, objCount=0; // Integer overflow ??
        // load URL's from a file
        File finput = new File("./resources/URL.txt");
        FileInputStream fis = new FileInputStream(finput);
        BufferedReader br = new BufferedReader(new InputStreamReader(fis));
        String line = null;
        HttpConnect httpConnect = new HttpConnect();

        while ((line = br.readLine()) != null) {
            //urlList.add(line);
            // For each url - extract all possible triplets
            JSONObject jsonObject = httpConnect.getJSONObjFromURL(line);
            JSONArray entityArr = (JSONArray) jsonObject.get("entities");
            JSONArray relationsArr = (JSONArray) jsonObject.get("relations");

            Iterator iter = entityArr.iterator();   //Iterate through the entity array
            String word, id, relation;
            while (iter.hasNext()) {
                jsonObject = (JSONObject) iter.next();
                word = (String) jsonObject.get("value");
                id  = (String) jsonObject.get("id");
                if (!dict.containsKey(id)) {
                    //dict.put(word, id);
                    dict.put(id, word);
                }
            }

            iter = relationsArr.iterator();
            JSONArray tmpJSONArr;
            JSONObject tmpJSONObj;
            String tmpStr="";
            int row, col;
            while (iter.hasNext()) {
                jsonObject = (JSONObject) iter.next();
                relation = (String) jsonObject.get("relation");
                //relation = relation.replaceAll("_", " ");    // No need to split now. Split when comparing similarity
                tmpJSONArr = (JSONArray) jsonObject.get("edges");
                Iterator iter2 = tmpJSONArr.iterator();
                while (iter2.hasNext()) {
                    tmpJSONObj = (JSONObject) iter2.next();

                    id = (String) tmpJSONObj.get("subject");
                    if (!dict.containsKey(id)) {
                        throw new NoSuchElementException();
                    } else {
                        tmpStr = dict.get(id);
                        if (subDict.containsKey(tmpStr)) {
                            row = subDict.get(tmpStr);
                        } else {
                            row = subCount;
                            subDict.put(tmpStr, subCount++);
                        }
                    }

                    id = (String) tmpJSONObj.get("object");
                    if (!dict.containsKey(id)) {
                        throw new NoSuchElementException();
                    } else {
                        tmpStr = dict.get(id);
                        if (objDict.containsKey(tmpStr)) {
                            col = objDict.get(tmpStr);
                        } else {
                            col = objCount;
                            objDict.put(tmpStr, objCount++);
                        }
                    }

                    tmpStr = row + "_" + col;
                    Set<String> hashSet;
                    //insert into knowledge base
                    if (kBase.containsKey(tmpStr)) {
                        hashSet = kBase.get(tmpStr);
                    } else {
                        hashSet = new HashSet<>();
                    }

                    hashSet.add(relation);
                    kBase.put(tmpStr, hashSet);
                }
            }
            dict.clear();   // Necessary as another url may create same ids for different words
        }
    }
}