<?php
session_start();

if (empty($_SESSION["money"])) {
	$_SESSION["money"] = 0;
}

if ($_POST["mode"] == "iine") {
	$_SESSION["did_iine"] = TRUE;
	$_SESSION["money"] += 1000;
	header("Location: /");
}

if ($_POST["mode"] == "buy") {
	if ($_POST["item"] == "background-red") {
		$_SESSION["has_background_red"] = TRUE;
		$_SESSION["money"] -= 100;
	}
	if ($_POST["item"] == "background-blue") {
		$_SESSION["has_background_blue"] = TRUE;
		$_SESSION["money"] -= 100;
	}
	if ($_POST["item"] == "background-yellow") {
		$_SESSION["has_background_yellow"] = TRUE;
		$_SESSION["money"] -= 100;
	}
	if ($_POST["item"] == "flag") {
		$_SESSION["has_flag"] = TRUE;
		$_SESSION["money"] -= 10000;
	}
	header("Location: /");
}
?>
<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://unpkg.com/bulma@0.7.4/css/bulma.min.css" />
	<style>
		body {
			padding: 3rem;
		}
		.content {
			text-align: center;
		}
		button {
			vertical-align: middle;
		}
	</style>
	<?php if ($_SESSION["has_background_red"]) { ?>
		<style>
			html {
				background: red;
			}
		</style>
	<?php } ?>
	<?php if ($_SESSION["has_background_blue"]) { ?>
		<style>
			html {
				background: blue;
			}
		</style>
	<?php } ?>
	<?php if ($_SESSION["has_background_yellow"]) { ?>
		<style>
			html {
				background: yellow;
			}
		</style>
	<?php } ?>
</head>

<body>
<div class="content">
	<h1>現在の残高: <?= $_SESSION["money"] ?>ポイント</h1>
	<?php if ($_SESSION["has_flag"]) { ?>
		<p><code>TSGCTF{kanikani_crab_life}</code></p>
	<?php } ?>
	<p>ただいまキャンペーン実施中! いいね!して1000ポイント分の残高をGET!</p>
	<form method="POST">
		<input type="hidden" name="mode" value="iine">
		<?php if ($_SESSION["did_iine"]) { ?>
			<button type="submit" class="button" disabled>いいね!する</button>
		<?php } else { ?>
			<button type="submit" class="button">いいね!する</button>
		<?php } ?>
	</form>
	<?php if ($_SESSION["did_iine"]) { ?>
		<p><small class="has-text-danger">※いいね!できるのは1日に1回までです。</small></p>
	<?php } ?>
	<h2>商品一覧</h2>
	<h3>オプション：赤背景</h3>
	<p>背景が赤くなります。かに座のあなたにぴったり!</p>
	<form method="POST">
		<input type="hidden" name="mode" value="buy">
		<input type="hidden" name="item" value="background-red">
		<strong style="vertical-align: middle">100ポイント</strong>
		<?php if ($_SESSION["has_background_red"]) { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※購入済みです。</small></p>
		<?php } else if ($_SESSION["money"] >= 100) { ?>
			<button type="submit" class="button">購入する</button>
		<?php } else { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※残高が足りません。</small></p>
		<?php } ?>
	</form>
	<h3>オプション：青背景</h3>
	<p>背景が青くなります。うお座のあなたにぴったり!</p>
	<form method="POST">
		<input type="hidden" name="mode" value="buy">
		<input type="hidden" name="item" value="background-blue">
		<strong style="vertical-align: middle">100ポイント</strong>
		<?php if ($_SESSION["has_background_blue"]) { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※購入済みです。</small></p>
		<?php } else if ($_SESSION["money"] >= 100) { ?>
			<button type="submit" class="button">購入する</button>
		<?php } else { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※残高が足りません。</small></p>
		<?php } ?>
	</form>
	<h3>オプション：黄背景</h3>
	<p>背景が黄色くなります。てんびん座のあなたにぴったり!</p>
	<form method="POST">
		<input type="hidden" name="mode" value="buy">
		<input type="hidden" name="item" value="background-yellow">
		<strong style="vertical-align: middle">100ポイント</strong>
		<?php if ($_SESSION["has_background_yellow"]) { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※購入済みです。</small></p>
		<?php } else if ($_SESSION["money"] >= 100) { ?>
			<button type="submit" class="button">購入する</button>
		<?php } else { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※残高が足りません。</small></p>
		<?php } ?>
	</form>
	<h3>オプション：フラグ</h3>
	<p>フラグが表示されます。オリオン座のあなたにぴったり!</p>
	<form method="POST">
		<input type="hidden" name="mode" value="buy">
		<input type="hidden" name="item" value="flag">
		<strong style="vertical-align: middle">10000ポイント</strong>
		<?php if ($_SESSION["has_flag"]) { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※購入済みです。</small></p>
		<?php } else if ($_SESSION["money"] >= 10000) { ?>
			<button type="submit" class="button">購入する</button>
		<?php } else { ?>
			<button type="submit" class="button" disabled>購入する</button>
			<p><small class="has-text-danger">※残高が足りません。</small></p>
		<?php } ?>
	</form>
</div>

</body>

</html>
