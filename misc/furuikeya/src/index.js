const {RTMClient, WebClient} = require('@slack/client');
const rtm = new RTMClient(process.env.SLACK_TOKEN);
const slack = new WebClient(process.env.SLACK_TOKEN);
const postFlag = require('./postFlag');

rtm.on('message', async (message) => {
    console.log(message);
    if (message.text.endsWith('を池に落としてしまいました！！！')) {
        const ax = message.text.slice(0, -'を池に落としてしまいました！！！'.length);
        const text = `あなたが落としたのは金の${ax}ですか？それとも銀の${ax}ですか？`;
        const reply = await slack.chat.postMessage({channel: message.channel, text});
        if (reply.message.text !== text) {
            await postFlag(slack, {channel: message.channel});
        }
    }
});

rtm.start();