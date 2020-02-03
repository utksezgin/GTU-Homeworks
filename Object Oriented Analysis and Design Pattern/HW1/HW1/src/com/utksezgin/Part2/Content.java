package com.utksezgin.Part2;

enum contentType{ text, audio, photo};

/**
 * Content of the subscribee.
 */
public abstract class Content {
    contentType type;
    String content = "";

    /**
     * @return Content in String format
     */
    public String getContent(){
        return content;
    }

    /**
     * @param newContent new content
     */
    public void setContent(String newContent){
        content = newContent;
    }
}

/**
 * Text content
 */
class TextContent extends Content{
    public TextContent(){
        this.type = contentType.text;
    }
}

/**
 * Audio content
 */
class AudioContent extends Content{
    public AudioContent(){
        this.type = contentType.audio;
    }
}

/**
 * Photo Content
 */
class PhotoContent extends Content{
    public PhotoContent(){
        this.type = contentType.photo;
    }
}