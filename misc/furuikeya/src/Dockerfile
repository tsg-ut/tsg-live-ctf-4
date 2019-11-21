FROM node:10

WORKDIR /app

COPY ./package*.json ./

RUN npm i

COPY ./index.js ./
COPY ./postFlag.js ./

CMD ["node", "index.js"]
