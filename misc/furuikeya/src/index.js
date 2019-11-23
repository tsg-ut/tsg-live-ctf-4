const {RTMClient, WebClient} = require('@slack/client');
const rtm = new RTMClient(process.env.SLACK_TOKEN);
const slack = new WebClient(process.env.SLACK_TOKEN);
const postFlag = require('./postFlag');

const pond = {
    'その辺で売ってる普通の斧': (channel) => {slack.chat.postMessage({channel, text:'普通の斧がありましたよ！'})},
    'ギラギラと輝く白銀色の斧': (channel) => {slack.chat.postMessage({channel, text:'銀の斧がありましたよ！'})},
    'ピカピカに光る黄金色の斧': (channel) => {slack.chat.postMessage({channel, text:'金の斧がありましたよ！'})},
    'f': (channel) => {slack.chat.postMessage({channel, text:`\`${process.env.FLAG}\``})},
}

rtm.on('message', async (message) => {
    if (!message.channel.startsWith('D')) {
        // not available in public channels
        return;
    }
    const match = message.text.match(/^(?<obj>.+)が池に落ちちゃった$/);
    if (match) {
        await slack.chat.postMessage({channel: message.channel, text:':statue_of_liberty:「あらあら，かわいそうに。わたしが探してあげましょう。」'});
        for (kind of ['その辺で売ってる普通の', 'ギラギラと輝く白銀色の', 'ピカピカに光る黄金色の']) {
            const text = [
                ':statue_of_liberty:「どのようなものかわからないけれど，試しに',
                kind,
                match.groups.obj,
                'を探してみますわ。どこかにあればいいのだけれど。」'
            ];
            const reply = await slack.chat.postMessage({channel: message.channel, text:text.join('')});

            const obj = reply.message.text.slice(text[0].length, -text[3].length);
            if (pond[obj]) {
                pond[obj](message.channel);
            } else {
                slack.chat.postMessage({channel: message.channel, text:':statue_of_liberty:「見つからなかったわ……ごめんなさい。」'});
            }
        }
    }
});

rtm.start();
