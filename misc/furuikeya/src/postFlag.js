module.exports = (slack, args) => {
    slack.chat.postMessage(
        Object.assign({}, args, {
            text: `\`${process.env.FLAG}\``,
            blocks:[
                {
                    type: 'section',
                    text: {
                        type: 'mrkdwn',
                        text: ':statue_of_liberty:「探しものは見つかりませんでした……代わりと言ってはなんですが，川底にあったものを差し上げましょう。」',
                    }
                }
            ]
        })
    );
};
