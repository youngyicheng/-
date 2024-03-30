#include <iostream>
#include <string>

// 目标接口
class MediaPlayer {
public:
    virtual void play(std::string audioType, std::string file) = 0;
};

// 被适配者接口
class AdvancedMediaPlayer {
public:
    virtual void playVlc(std::string file) = 0;
};

// 具体的被适配者
class VlcPlayer : public AdvancedMediaPlayer {
public:
    void playVlc(std::string file) override {
        std::cout << "Playing VLC file: " << file << std::endl;
    }
};

// 适配器
class MediaAdapter : public MediaPlayer {
private:
    AdvancedMediaPlayer *advancedPlayer;

public:
    MediaAdapter(std::string audioType) {
        if (audioType == "vlc" || audioType == "mp4") {
            advancedPlayer = new VlcPlayer();
        } else {
            advancedPlayer = nullptr;
        }
    }

    void play(std::string audioType, std::string file) override {
        if (audioType == "vlc" && advancedPlayer != nullptr) {
            advancedPlayer->playVlc(file);
        } else {
            std::cout << "Invalid media type: " << audioType << std::endl;
        }
    }
};

// 客户端
class AudioPlayer : public MediaPlayer {
public:
    void play(std::string audioType, std::string file) override {
        if (audioType == "mp3") {
            std::cout << "Playing MP3 file: " << file << std::endl;
        } else if (audioType == "vlc" || audioType == "mp4") {
            MediaAdapter *mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, file);
            delete mediaAdapter;
        } else {
            std::cout << "Invalid media type: " << audioType << std::endl;
        }
    }
};

// 客户端调用
int main() {
    AudioPlayer audioPlayer;
    audioPlayer.play("mp3", "song.mp3");
    audioPlayer.play("vlc", "film.vlc");

    return 0;
}
/*在上面的C++示例中，实现了适配器模式。让我们来分析一下各个类之间的关系：

1. **MediaPlayer（目标接口）**：这是一个抽象类，定义了客户端代码期望的播放器接口。在示例中，`AudioPlayer` 类实现了这个接口，它提供了一个通用的 `play` 方法用于播放不同类型的音频文件。

2. **AdvancedMediaPlayer（被适配者接口）**：同样也是一个抽象类，定义了高级播放器的接口。在示例中，`VlcPlayer` 类实现了这个接口，提供了播放 VLC 格式音频文件的功能。

3. **VlcPlayer（具体的被适配者）**：这是一个具体的类，实现了 `AdvancedMediaPlayer` 接口，提供了播放 VLC 格式音频文件的功能。

4. **MediaAdapter（适配器）**：这是一个适配器类，它实现了 `MediaPlayer` 接口，并持有一个 `AdvancedMediaPlayer` 对象作为成员。根据客户端的请求，它将其收到的播放请求转发给被适配者对象（在这里是 `VlcPlayer`），从而完成播放操作。

5. **AudioPlayer（客户端）**：这是客户端代码，使用 `MediaPlayer` 接口来播放音频文件。它可以播放 MP3 文件，而对于其他格式的文件（比如 VLC），它会创建一个适配器对象（`MediaAdapter`）来处理播放请求。

在这个结构中，适配器模式的核心是 `MediaAdapter` 类，它充当了客户端代码和被适配者（`VlcPlayer`）之间的桥梁，使得客户端代码可以通过统一的接口调用被适配者的功能，而无需了解被适配者的实现细节。*/