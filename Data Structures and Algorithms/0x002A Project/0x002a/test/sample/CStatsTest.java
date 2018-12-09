package sample;

import javafx.util.Pair;
import org.junit.Assert;
import org.junit.Test;

import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.Set;

public class CStatsTest
{

    @Test
    public void updateAllStats()
    {
        HashMap<String, Integer> map = new HashMap<>();
        HashMap<String, Pair<Character, Integer>> updater = new HashMap<>();
        updater.put("Ozellik 1", new Pair<>('-', 4));
        updater.put("Ozellik 2", new Pair<>('+', 5));
        updater.put("Ozellik 3", new Pair<>('/', 2));
        map.put("Ozellik 1", 4);
        map.put("Ozellik 2", 5);
        map.put("Ozellik 3", 6);
        CStats workon = new CStats(map);
        workon.updateAllStats(updater);
        map.replace("Ozellik 1", 0);
        map.replace("Ozellik 2", 10);
        map.replace("Ozellik 3", 3);
        String ret_val = "";
        Set<String> keyV = map.keySet();
        for(String outp : keyV)
            ret_val += outp + ": " + map.get(outp).toString();
        Assert.assertEquals(ret_val, workon.toString());
    }

    @Test
    public void updateStats()
    {
        HashMap<String, Integer> map = new HashMap<>();
        map.put("Ozellik 1", 4);
        map.put("Ozellik 2", 5);
        map.put("Ozellik 3", 6);
        CStats workon = new CStats(map);
        workon.updateStats("Ozellik 1", '-', 4);
        map.replace("Ozellik 1", 0);
        String ret_val = "";
        Set<String> keyV = map.keySet();
        for(String outp : keyV)
            ret_val += outp + ": " + map.get(outp).toString();
        Assert.assertEquals(ret_val, workon.toString());
        workon.updateStats("Ozellik 2", '+', 5);

        map.replace("Ozellik 2", 10);
        ret_val = "";
        for(String outp : keyV)
            ret_val += outp + ": " + map.get(outp).toString();
        Assert.assertEquals(ret_val, workon.toString());
        workon.updateStats("Ozellik 3", '/', 2);
        map.replace("Ozellik 3", 3);

        ret_val = "";
        for(String outp : keyV)
            ret_val += outp + ": " + map.get(outp).toString();
        Assert.assertEquals(ret_val, workon.toString());

    }

    @Test
    public void addParam()
    {
        CStats workon = new CStats();
        Assert.assertEquals(true, workon.addParam("first"));
        Assert.assertEquals(false, workon.addParam("first"));
        Assert.assertEquals(true, workon.addParam("sec"));
        Assert.assertEquals(false, workon.addParam("sec"));
        Assert.assertEquals(true, workon.addParam("third"));
        Assert.assertEquals(false, workon.addParam("first"));
    }

    @Test
    public void addParam1() {
        CStats workon = new CStats();
        Assert.assertEquals(true, workon.addParam("first", -1));
        Assert.assertEquals(false, workon.addParam("first", 1));
        Assert.assertEquals(true, workon.addParam("sec", 1));
        Assert.assertEquals(false, workon.addParam("sec", 4));
        Assert.assertEquals(true, workon.addParam("third", 23));
        Assert.assertEquals(false, workon.addParam("first", 11));
    }

    @Test
    public void getStats()
    {
        Set<String> MyString = new LinkedHashSet<>();
        MyString.add("Ozellik 1");
        MyString.add("Ozellik 2");
        MyString.add("Ozellik 3");
        MyString.add("Ozellik 4");
        CStats adder = new CStats();
        for(String i : MyString)
            adder.addParam(i);
        Assert.assertEquals(MyString, adder.getStats());
    }

    @Test
    public void toSave()
    {
        HashMap<String, Integer> map = new HashMap<>();
        map.put("Ozellik 1", 4);
        map.put("Ozellik 2", 5);
        map.put("Ozellik 3", 6);
        CStats workon = new CStats(map);

        String ret_val = "<";
            Set<String> keyV = map.keySet();
            for(String outp : keyV)
                ret_val += outp + ":" + map.get(outp).toString() + ",";
        ret_val += ">";
        Assert.assertEquals(ret_val, workon.toSave());
    }
}