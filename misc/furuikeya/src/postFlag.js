module.exports = (slack, args) => {
    slack.chat.postMessage(
        Object.assign({}, args, {
            text: `\`${process.env.FLAG}\``,
            blocks:[
                {
                    type: 'section',
                    text: {
                        type: 'mrkdwn',
                        text: "いたずら好きのあなたにはフラグを差し上げましょう。"
                    }
                }
            ]
        })
    );
};
