<template>
  <div>
    <nuxt />
  </div>
</template>

<script>
export default {
  mounted() {
    window.addEventListener('contextmenu', (event) => {
      event.preventDefault();
      alert('右クリック禁止！');
    });
  },
};
</script>

<style>
html {
  background: black;
  color: white;
  font-family: 'MS PGothic';
}
</style>
